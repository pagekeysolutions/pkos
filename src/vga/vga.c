#include "vga.h"
#include "../kernel/kernel.h"
#include "../memory/memory.h"
#include "../screen/screen.h"
#include "../common/stdlib.h"
#include "../common/debug.h"
#include "reg_ac.h"
#include "reg_crtc.h"
#include "reg_ext.h"
#include "reg_gc.h"
#include "reg_seq.h"
#include "vga_config.h"
#include "font.h"

#include <stdint.h>
#include <stdarg.h>

#define COLOR_BLACK 0x0
#define COLOR_DARK_BLUE 0x1
#define COLOR_GREEN 0x2
#define COLOR_TEAL 0x3
#define COLOR_RED 0x4
#define COLOR_PURPLE 0x5
#define COLOR_YELLOW 0x6
#define COLOR_GRAY 0x7
#define COLOR_NAVY 0x8
#define COLOR_BLUE 0x9
#define COLOR_LIGHT_GREEN 0xA
#define COLOR_SKY_BLUE 0xB
#define COLOR_MAROON 0xC
#define COLOR_BRIGHT_PURPLE 0xD
#define COLOR_BEIGE 0xE
#define COLOR_INDIGO 0xF
#define COLOR_WHITE 0x3F


u32 vga_mode_var = 0;

#define VGA_TEXT_MODE_COLS 80
#define VGA_TEXT_MODE_ROWS 25
#define VGA_TEXT_MODE_SIZE (VGA_TEXT_MODE_COLS * VGA_TEXT_MODE_ROWS)

static u16 vga_text_mode_backup[VGA_TEXT_MODE_SIZE];

#define CURRENT (_sbuffers[_sback])
#define SWAP() (_sback = 1 - _sback)

static u8 *VGA_MEM_BUF = (u8 *) VGA_MEM_ADDR;

//double buffers
u8 _sbuffers[2][VGA_SCREEN_SIZE];
u8 _sback = 0;


u8 g_320x200x256[] = {
/* MISC */
	0x63,
/* SEQ */
	0x03, 0x01, 0x0F, 0x00, 0x0E,
/* CRTC */
	0x5F, 0x4F, 0x50, 0x82, 0x54, 0x80, 0xBF, 0x1F,
	0x00, 0x41, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x9C, 0x0E, 0x8F, 0x28,	0x40, 0x96, 0xB9, 0xA3,
	0xFF,
/* GC */
	0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x05, 0x0F,
	0xFF,
/* AC */
	0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
	0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F,
	
};

u8 g_80x25_text[] =
{
/* MISC */
	0x67,
/* SEQ */
	0x03, 0x00, 0x03, 0x00, 0x02,
/* CRTC */
	0x5F, 0x4F, 0x50, 0x82, 0x55, 0x81, 0xBF, 0x1F,
	0x00, 0x4F, 0x0D, 0x0E, 0x00, 0x00, 0x00, 0x50,
	0x9C, 0x0E, 0x8F, 0x28, 0x1F, 0x96, 0xB9, 0xA3,
	0xFF,
/* GC */
	0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x0E, 0x00,
	0xFF,
/* AC */
	0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x14, 0x07,
	0x38, 0x39, 0x3A, 0x3B, 0x3C, 0x3D, 0x3E, 0x3F,
	0x0C, 0x00, 0x0F, 0x08, 0x00
};


/* This flag is a bit of a hack. We do not need to continuously backup the palette data.
   I have noticed corruption on multiple switches. 
   It would likely be best to get a clean dump of the palette data and use that as a hardcoded data set
   instead of backing it up every time.
*/
bool palette_data_is_valid = false;
uint8_t palette_256_backup_data[256 * 3];

#define VGA_PALETTE_INDEX 0x3C8

// Method to get all of the 256 color palette data before switching to VGA mode
void vga_backup_palette_256()
{
	if(palette_data_is_valid) 
	{
		return;
	}

	// Set the palette index to 0 to start reading colors
	ioport_out(VGA_PALETTE_INDEX, 0);

	// Read the palette data for all 256 colors
	for (int i = 0; i < 256; i++)
	{
		// Read the red component
		palette_256_backup_data[i * 3] = ioport_in(VGA_PALETTE_DATA);
		// Read the green component
		palette_256_backup_data[i * 3 + 1] = ioport_in(VGA_PALETTE_DATA);
		// Read the blue component
		palette_256_backup_data[i * 3 + 2] = ioport_in(VGA_PALETTE_DATA);
	}

	palette_data_is_valid = true;
}

void vga_restore_palette_256(const uint8_t *palette_data)
{
	// Set the palette index to 0 to start writing colors
	ioport_out(VGA_PALETTE_INDEX, 0);

	// Write the palette data for all 256 colors
	for (int i = 0; i < 256; i++)
	{
		// Write the red component
		ioport_out(VGA_PALETTE_DATA, palette_data[i * 3]);
		// Write the green component
		ioport_out(VGA_PALETTE_DATA, palette_data[i * 3 + 1]);
		// Write the blue component
		ioport_out(VGA_PALETTE_DATA, palette_data[i * 3 + 2]);
	}
}

void vmemwr(uint32_t dst_off, uint8_t *src, uint32_t count, uint32_t base_addr) 
{
    uint8_t *dst = (uint8_t *)(base_addr + dst_off);
    while (count--) {
        *dst++ = *src++;
    }
}

static void set_plane(unsigned p)
{
	unsigned char pmask;

	p &= 3;
	pmask = 1 << p;
	/* set read plane */
	ioport_out(VGA_GC_INDEX, 4);
	ioport_out(VGA_GC_DATA, p);
	/* set write plane */
	ioport_out(VGA_SEQ_INDEX, 2);
	ioport_out(VGA_SEQ_DATA, pmask);
}

static void vga_write_font(unsigned char *buf, unsigned font_height)
{
	unsigned char seq2, seq4, gc4, gc5, gc6;
	unsigned i;

/* save registers
set_plane() modifies GC 4 and SEQ 2, so save them as well */
	ioport_out(VGA_SEQ_INDEX, 2);
	seq2 = ioport_in(VGA_SEQ_DATA);

	ioport_out(VGA_SEQ_INDEX, 4);
	seq4 = ioport_in(VGA_SEQ_DATA);
/* turn off even-odd addressing (set flat addressing)
assume: chain-4 addressing already off */
	ioport_out(VGA_SEQ_DATA, seq4 | 0x04);

	ioport_out(VGA_GC_INDEX, 4);
	gc4 = ioport_in(VGA_GC_DATA);

	ioport_out(VGA_GC_INDEX, 5);
	gc5 = ioport_in(VGA_GC_DATA);
/* turn off even-odd addressing */
	ioport_out(VGA_GC_DATA, gc5 & ~0x10);

	ioport_out(VGA_GC_INDEX, 6);
	gc6 = ioport_in(VGA_GC_DATA);
/* turn off even-odd addressing */
	ioport_out(VGA_GC_DATA, gc6 & ~0x02);
/* write font to plane P4 */
	set_plane(2);
/* write font 0 */
	for(i = 0; i < 256; i++)
	{
		vmemwr(16384u * 0 + i * 32, buf, font_height, 0xB8000);
		buf += font_height;
	}
// #if 0
// /* write font 1 */
// 	for(i = 0; i < 256; i++)
// 	{
// 		vmemwr(16384u * 1 + i * 32, buf, font_height);
// 		buf += font_height;
// 	}
// #endif

/* restore registers */
	ioport_out(VGA_SEQ_INDEX, 2);
	ioport_out(VGA_SEQ_DATA, seq2);
	ioport_out(VGA_SEQ_INDEX, 4);
	ioport_out(VGA_SEQ_DATA, seq4);
	ioport_out(VGA_GC_INDEX, 4);
	ioport_out(VGA_GC_DATA, gc4);
	ioport_out(VGA_GC_INDEX, 5);
	ioport_out(VGA_GC_DATA, gc5);
	ioport_out(VGA_GC_INDEX, 6);
	ioport_out(VGA_GC_DATA, gc6);
}

static void vga_set_text_mode_palette() {
    // The default palette for text mode
	unsigned char palette[48] = {
		0x00, 0x00, 0x00, // black
		0x00, 0x00, 0x2A, // blue
		0x00, 0x2A, 0x00, // green
		0x00, 0x2A, 0x2A, // cyan
		0x2A, 0x00, 0x00, // red
		0x2A, 0x00, 0x2A, // magenta
		0x2A, 0x2A, 0x00, // brown
		0x2A, 0x2A, 0x2A, // light gray
		0x00, 0x00, 0x15, // dark gray
		0x00, 0x00, 0x3F, // light blue
		0x00, 0x2A, 0x15, // light green
		0x00, 0x2A, 0x3F, // light cyan
		0x2A, 0x00, 0x15, // light red
		0x2A, 0x00, 0x3F, // light magenta
		0x2A, 0x2A, 0x15, // yellow
		0x2A, 0x2A, 0x3F  // white
	};

    // Write the palette to the DAC
    ioport_out(0x3C8, 0);  // Start at the first color
    for (int i = 0; i < 48; i++) {
        ioport_out(0x3C9, palette[i]);
	}
}



u32 get_reg(u32 address, u32 data, u32 index) {
    /**
        Get the value of a register using ioports.
    */
    // Save the current value of the address register
    u32 saved_addr_reg = ioport_in(address);
    // Set the address register to indicate where we will read
	ioport_out(address, index);
    // Get the data from that address
	u32 result = ioport_in(data);
    // Restore the original value of the address register
	ioport_out(address, saved_addr_reg);
    // Return the result
	return result;
}

u32 set_reg(u32 address, u32 data, u32 index, u32 value) {
    /**
        Set the value of a register using ioports.
    */
    // Save the current value of the address register
	u32 saved_addr_reg = ioport_in(address);
    // Set the address to which we are writing
	ioport_out(address, index);
    // Set the value at that address by writing to the data port
	ioport_out(data, value);
    // Restore the original value of the address register
	ioport_out(address, saved_addr_reg);
}



void vga_info() {
	struct VGA vga;
	get_vga(&vga);
	print_vga(vga);
}

void vga_font() {
	// Change font
	u8 curFont = get_reg_seq(VGA_SEQ_REG_CHAR);
	u8 primaryBit0 = (curFont >> 4) & 1;
	u8 primaryBits1_2 = curFont & 0b11;
	u8 charSetA = (primaryBits1_2 << 1) | primaryBit0;
	print("curfont: 0b");
	println(itoab(charSetA));
	// set_reg_seq(VGA_SEQ_REG_CHAR, 0b10000);

	println("abcdefghijklmnopqrstuvwxyz");
	println("?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[]");
	println("1234567890!?-*");
	println("hello world");
	// change font for character map A
}

#define VID_BACKUP_SRC 0xB8000
#define VID_BACKUP_DEST 0x10B800
#define VID_BACKUP_AMOUNT 0xFFF

void backup_vidmem() {
	//debug_printf("Backing up video memory from 0x%X\n", VID_BACKUP_SRC);
    u16* text_ptr = (u16 *) VID_BACKUP_SRC;
    for(int i = 0; i < VGA_TEXT_MODE_SIZE; i++) {
        u16 cell = text_ptr[i];
        unsigned char ch = cell & 0xFF; // Extract character
        unsigned char attr = (cell >> 8) & 0xFF; // Extract attribute
		//debug_printf("Backing up character (%c, 0x%X) with attribute 0x%X at 0x%X\n", ch, ch, attr, text_ptr + i);

        // Store character and attribute in the backup array
        vga_text_mode_backup[i] =  text_ptr[i];
    }
}

void restore_vidmem() {
    u16 *text_ptr = (u16 *) VID_BACKUP_SRC;
    for(int i = 0; i< VGA_TEXT_MODE_SIZE; i++) {
        u16 cell = vga_text_mode_backup[i];
        unsigned char ch = cell & 0xFF; // Extract character
        unsigned char attr = (cell >> 8) & 0xFF; // Extract attribute

		//debug_printf("Restoring character (%c, 0x%X) with attribute 0x%X from 0x%X\n", ch, ch, attr, text_ptr + i);

        // Restore character and attribute from the backup array
        text_ptr[i] = vga_text_mode_backup[i];
    }
}

void turn_off_sequencer() {
	set_reg_seq(VGA_SEQ_REG_RESET, 0x1);
}
void turn_on_sequencer() {
	set_reg_seq(VGA_SEQ_REG_RESET, 0x3);
}

void vga_write_regs(u8 *regs, bool is_text_mode) {
	/* ORDER IS IMPORTANT HERE 
		- STEPS:
			- write misc. reg (no abstraction structure present)
			- write sequencer regs
			- unlock CRTC regs
				- make sure they remain unlocked
			- write CRTC regs
			- write graphics controller regs
			- write attribute controller regs
			- configure 256 color pallette if VGA, lock 16 color pallette if not
	*/

	u32 i;

/* write MISCELLANEOUS reg */
	ioport_out(VGA_MISC_WRITE, *regs);
	regs++;
/* write SEQUENCER regs */
	for(i = 0; i < VGA_NUM_SEQ_REGS; i++)
	{
		ioport_out(VGA_SEQ_INDEX, i);
		ioport_out(VGA_SEQ_DATA, *regs);
		regs++;
	}
/* unlock CRTC registers */
	ioport_out(VGA_CRTC_INDEX, 0x03);
	ioport_out(VGA_CRTC_DATA, ioport_in(VGA_CRTC_DATA) | 0x80);
	ioport_out(VGA_CRTC_INDEX, 0x11);
	ioport_out(VGA_CRTC_DATA, ioport_in(VGA_CRTC_DATA) & ~0x80);
/* make sure they remain unlocked */
	regs[0x03] |= 0x80;
	regs[0x11] &= ~0x80;
/* write CRTC regs */
	for(i = 0; i < VGA_NUM_CRTC_REGS; i++)
	{
		ioport_out(VGA_CRTC_INDEX, i);
		ioport_out(VGA_CRTC_DATA, *regs);
		regs++;
	}
/* write GRAPHICS CONTROLLER regs */
	for(i = 0; i < VGA_NUM_GC_REGS; i++)
	{
		ioport_out(VGA_GC_INDEX, i);
		ioport_out(VGA_GC_DATA, *regs);
		regs++;
	}
/* write ATTRIBUTE CONTROLLER regs */
	for(i = 0; i < VGA_NUM_AC_REGS; i++)
	{
		(void)ioport_in(VGA_INSTAT_READ);
		ioport_out(VGA_AC_INDEX, i);
		ioport_out(VGA_AC_WRITE, *regs);
		regs++;
	}

	if(is_text_mode) {
		//restore_text_mode_palette();
		/* lock 16-color palette and unblank display */
		(void)ioport_in(VGA_INSTAT_READ);
		ioport_out(VGA_AC_INDEX, 0x20);
	}
	else {
		/* THIS BLOCK NEEDS SOME INVESTIGATIONS 
			- is this valid palette data?
			- can this be improved?
		*/
		/* Configure 256 color pallette */
		ioport_out(VGA_AC_INDEX, 0x20);

		ioport_out(VGA_PALETTE_MASK, 0xFF);
		ioport_out(VGA_PALETTE_WRITE, 0);
		for (uint8_t i = 0; i < 255; i++) {
			ioport_out(VGA_PALETTE_DATA, (((i >> 5) & 0x7) * (256 / 8)) / 4);
			ioport_out(VGA_PALETTE_DATA, (((i >> 2) & 0x7) * (256 / 8)) / 4);
			ioport_out(VGA_PALETTE_DATA, (((i >> 0) & 0x3) * (256 / 4)) / 4);
		}

		// set color 255 = white
		ioport_out(VGA_PALETTE_WRITE, 0);
		ioport_out(VGA_PALETTE_DATA, 0x3F);
		ioport_out(VGA_PALETTE_DATA, 0x3F);
		ioport_out(VGA_PALETTE_DATA, 0x3F);
	}
}

static void vga_xor() {
    for(int x = 0; x < VGA_SCREEN_WIDTH; x++) {
        for(int y = 0; y < VGA_SCREEN_HEIGHT; y++) {
        	uint8_t color = VALUE_TO_COLOR(x ^ y);
			vga_plot_pixel(x, y, color);
        }
    }
}


void vga_flip() 
{
    memcpy(VGA_MEM_BUF, &CURRENT, VGA_SCREEN_SIZE);
	SWAP();
}

#define PALETTE_SIZE 16 // Text mode uses 16 colors
unsigned char original_text_palette[PALETTE_SIZE * 3]; // 3 bytes per color

#define PALETTE_SIZE 16 // Text mode uses 16 colors
unsigned char original_text_palette[PALETTE_SIZE * 3]; // 3 bytes per color

void backup_text_mode_palette() {
    ioport_out(0x3C7, 0);  // Set the palette read address to 0
    debug_printf("Backing up text mode palette:\n");
    for (int i = 0; i < PALETTE_SIZE * 3; i++) {
        original_text_palette[i] = ioport_in(0x3C9);
        if (i % 3 == 0) { // New line for each color entry for readability
            debug_printf("\nColor %d: ", i / 3);
        }
        debug_printf("%X ", original_text_palette[i]);
    }
    debug_printf("\n"); // New line after finishing backup
}

void restore_text_mode_palette() {
    ioport_out(0x3C8, 0);  // Set the palette write address to 0
    debug_printf("Restoring text mode palette:\n");
    for (int i = 0; i < PALETTE_SIZE * 3; i++) {
        ioport_out(0x3C9, original_text_palette[i]);
        if (i % 3 == 0) { // New line for each color entry for readability
            debug_printf("\nColor %d: ", i / 3);
        }
        debug_printf("%X ", original_text_palette[i]);
    }
    debug_printf("\n"); // New line after finishing restoration
}

void vga_enter() {
	// Using mode 13h (320x200 linear 256-color mode) from:
	// https://wiki.osdev.org/VGA_Hardware#List_of_register_settings

	if (vga_mode_var == 1) return;
	vga_mode_var = 1;
    println("Attempting to switch modes...");

	vga_backup_palette_256();
	
	backup_vidmem();
	backup_text_mode_palette();
	vga_write_regs(g_320x200x256, false);
	vga_clear_screen();

	vga_xor();
	vga_flip();
}

void vga_exit() {
	// Using mode 3h (80x25 text mode) from:
	// https://wiki.osdev.org/VGA_Hardware#List_of_register_settings
	
	if (vga_mode_var == 0) return;
    vga_mode_var = 0;

	// Disable video output during the switch
    ioport_out(VGA_SEQ_INDEX, 0x01);
    uint8_t seq1 = ioport_in(VGA_SEQ_DATA);
    ioport_out(VGA_SEQ_DATA, seq1 | 0x20); // Set bit 5 of Sequencer register 1 to 1 (Screen Off)

	vga_write_regs(g_80x25_text, true);
	
	vga_restore_palette_256(palette_256_backup_data);
	restore_text_mode_palette();
	
	vga_write_font(g_8x16_font, 16);
	
	//vga_set_text_mode_palette();

	// Re-enable video output after the switch
    ioport_out(VGA_SEQ_INDEX, 0x01);
    ioport_out(VGA_SEQ_DATA, seq1 & ~0x20); // Reset bit 5 to 0 (Screen On)

    restore_vidmem();

    print_prompt();
}

void draw_rectangle(int x, int y, int width, int height, int color) {
	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {
			vga_plot_pixel(x+i, y+j, color);
		}
	}
}

void draw_happy_face(int x, int y) {
	// eye
	vga_plot_pixel(x,y,COLOR_PURPLE);
	// eye
	vga_plot_pixel(x+10,y,COLOR_PURPLE);
	// mouth
	vga_plot_pixel(x,	y+8,COLOR_PURPLE);
	vga_plot_pixel(x+1,	y+9,COLOR_PURPLE);
	vga_plot_pixel(x+2,	y+10,COLOR_PURPLE);
	vga_plot_pixel(x+3,	y+10,COLOR_PURPLE);
	vga_plot_pixel(x+4,	y+10,COLOR_PURPLE);
	vga_plot_pixel(x+5,	y+10,COLOR_PURPLE);
	vga_plot_pixel(x+6,	y+10,COLOR_PURPLE);
	vga_plot_pixel(x+7,	y+10,COLOR_PURPLE);
	vga_plot_pixel(x+8,	y+10,COLOR_PURPLE);
	vga_plot_pixel(x+9,	y+9,COLOR_PURPLE);
	vga_plot_pixel(x+10,y+8,COLOR_PURPLE);
}

void vga_clear_screen() {
    // Note: "clear_screen" name conflicted with something in screen.h
    // Now I see why namespacing is a thing
    for (int i = 0; i < 320; i++) {
        for (int j = 0; j < 200; j++) {
            vga_plot_pixel(i,j,COLOR_BLACK);
        }
    }
}

static void vga_write_pixel8(uint32_t x, uint32_t y, uint32_t color) {
	uint32_t offset = VGA_SCREEN_WIDTH * y + x;
	CURRENT[offset] =  color;
}

void vga_plot_pixel(uint32_t x, uint32_t y, uint32_t color) {
    if (x >= VGA_SCREEN_WIDTH || y >= VGA_SCREEN_HEIGHT) {
        return;
    }

    vga_write_pixel8(x, y, color);
}


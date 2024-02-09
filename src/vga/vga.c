#include "vga.h"
#include "../kernel/kernel.h"
#include "../memory/memory.h"
#include "../screen/screen.h"

#define COLOR_BLACK 0x0
#define COLOR_GREEN 0x2
#define COLOR_PURPLE 0xf

#define GRAPHICS_REG_ADDR 0x3ce
#define GRAPHICS_REG_DATA 0x3cf
#define GRAPHICS_IDX_MISC 0x06

// EXT (External/General) Registers: http://www.osdever.net/FreeVGA/vga/extreg.htm
#define VGA_MISC_IN  0x3CC // Miscellaneous Output Register (read)
#define VGA_MISC_OUT 0x3C2 // Miscellaneous Output Register (write)

// SEQ (Sequencer) Registers: http://www.osdever.net/FreeVGA/vga/seqreg.htm
#define VGA_SEQ_ADDR 0x3C4
#define VGA_SEQ_DATA 0x3C5
#define VGA_SEQ_REG_RESET 0x00 // Reset Register
#define VGA_SEQ_REG_CLOCK 0x01 // Clocking Mode Register
#define VGA_SEQ_REG_MAP   0x02 // Map Mask Register
#define VGA_SEQ_REG_CHAR  0x03 // Character Map Select Register
#define VGA_SEQ_REG_MEM   0x04 // Sequencer Memory Mode Register

// CRTC (Cathode Ray Tube Controller): http://www.osdever.net/FreeVGA/vga/crtcreg.htm

// GC (Graphics Controller): http://www.osdever.net/FreeVGA/vga/graphreg.htm
struct GraphicsController {
	u8 regSetReset; 		// Set/Reset Register
	u8 regEnableSetReset; 	// Enable Set/Reset Register
	u8 regColorCompare;		// Color Compare Register
	u8 regDataRotate;  		// Data Rotate Register
	u8 regReadMap;			// Read Map Select Register
	u8 regGraphicsMode;		// Graphics Mode Register
	u8 regMisc;				// Miscellaneous Graphics Register
	u8 regColorDontCare;	// Color Don't Care Register
	u8 regBitMask;			// Bit Mask Register
};
#define VGA_GRAPHICS_ADDR 0x3ce
#define VGA_GRAPHICS_DATA 0x3cf
#define VGA_GRAPHICS_REG_SR 			0x00
#define VGA_GRAPHICS_REG_ENABLE_SR		0x01
#define VGA_GRAPHICS_REG_COLORCOMPARE	0x02
#define VGA_GRAPHICS_REG_DATAROTATE		0x03
#define VGA_GRAPHICS_REG_READMAP		0x04
#define VGA_GRAPHICS_REG_GRAPHICSMODE	0x05
#define VGA_GRAPHICS_REG_MISC 			0x06
#define VGA_GRAPHICS_REG_COLORDONTCARE	0x07
#define VGA_GRAPHICS_REG_BITMASK		0x08

// AC (Attribute Controller) Registers: http://www.osdever.net/FreeVGA/vga/attrreg.htm


unsigned int vga_mode_var = 0;

// Graphics Registers: 0x3ce = addr, 0x3cf = data
// see http://www.osdever.net/FreeVGA/vga/graphreg.htm
// Advice for accessing VGA registers: http://www.osdever.net/FreeVGA/vga/vgareg.htm
unsigned int get_graphics_reg(unsigned int index) {
	unsigned int saved_addr_reg = ioport_in(GRAPHICS_REG_ADDR);
	ioport_out(GRAPHICS_REG_ADDR, index);
	unsigned int graphics_reg_value = ioport_in(GRAPHICS_REG_DATA);
	ioport_out(GRAPHICS_REG_ADDR, saved_addr_reg); // restore address register
	return graphics_reg_value;
}
void set_graphics_reg(unsigned int index, unsigned int value) {
	unsigned int saved_addr_reg = ioport_in(GRAPHICS_REG_ADDR);
	ioport_out(GRAPHICS_REG_ADDR, index);
	ioport_out(GRAPHICS_REG_DATA, value);
	ioport_out(GRAPHICS_REG_ADDR, saved_addr_reg); // restore address register
}



void vga_info() {
	println("Getting VGA info");
	unsigned int misc_reg = get_graphics_reg(GRAPHICS_IDX_MISC);
	// RAM Enable: is VGA checking the memory set by CPU? (are we bothering to use mem-mapped I/O from CPU?)
	unsigned int ram_enable = (misc_reg & 0b10) >> 1;
	// Memory Map Select: which area of memory should be used to draw the screen?
	unsigned int mem_map_select = (misc_reg & 0b1100) >> 2;
	// Alphanumeric Disable: are we disabling text mode (and instead interpreting memory as pixels?)
	unsigned int alpha_dis = misc_reg & 1;
	// Pretty-print each of these fields
	print("RAM enable: ");
	if (ram_enable == 0) {
		println("disabled");
	} else {
		println("enabled");
	}
	print("Memory Map Select: 0b");
	char buffer[2];
	println(itoab(mem_map_select, buffer));
	print("Alphanumeric disable: 0b");
	println(itoa(alpha_dis, buffer));

}

void vga_enter() {
	if (vga_mode_var == 1) return;
	vga_mode_var = 1;
    println("Attempting to switch modes...");

	// Save video memory somewhere else
	// 0xb8000 to 0xbffff (32K)
	memcpy(0x0010b8000, 0xb8000, COLS*ROWS*2);

	// Set alphanumeric disable = 1
	unsigned int misc_reg = get_graphics_reg(GRAPHICS_IDX_MISC);
	misc_reg |= 1; // bit 0 is alphanumeric disable, set it to 1
	set_graphics_reg(GRAPHICS_IDX_MISC, misc_reg);

	memset(0xb8000, 0, 60);
	vga_clear_screen();
	vga_plot_pixel(0,0,COLOR_GREEN);
	vga_plot_pixel(1,0,COLOR_GREEN);
    vga_plot_pixel(1,1,COLOR_GREEN);
    vga_plot_pixel(2,1,COLOR_GREEN);
    vga_plot_pixel(2,2,COLOR_GREEN);
	// // draw rectangle
	// draw_rectangle(150, 10, 100, 50);
	// // draw some faces
	// draw_happy_face(10,10);
	// draw_happy_face(100,100);
	// draw_happy_face(300,150);
	// // bounds
	// vga_plot_pixel(0, 0, 15);
	// vga_plot_pixel(319, 199, COLOR_PURPLE);
	// // see some colors
	// for (int i = 0; i < 15; i++) {
	// 	for (int j = 0; j < 100; j++) {
	// 		vga_plot_pixel(i, 50+j, i);
	// 	}
	// }
	
}

void vga_exit() {
	if (vga_mode_var == 0) return;
	// Go back to alphanumeric disable 0
	unsigned int misc_reg = get_graphics_reg(GRAPHICS_IDX_MISC);
	misc_reg &= 0; // set alphanum disable back to 0
	misc_reg |= 0b10; // bit 1 is RAM enable, set it to 1
	misc_reg |= 0b1100; // set mem map select to 11
	set_graphics_reg(GRAPHICS_IDX_MISC, misc_reg);

	// Restore text-mode video memory
	memcpy(0xb8000, 0x0010b8000, COLS*ROWS*2);

	vga_mode_var = 0;

	print_prompt();
}

void draw_rectangle(int x, int y, int width, int height) {
	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {
			vga_plot_pixel(x+i, y+j, COLOR_GREEN);
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

void vga_plot_pixel(int x, int y, unsigned short color) {
    unsigned short offset = x + 320 * y;
	unsigned char *PLANE0 = (unsigned char*) PLANE0_ADDRESS;
    PLANE0[offset] = color;
	unsigned char *PLANE1 = (unsigned char*) PLANE1_ADDRESS;
    PLANE1[offset] = color;
	unsigned char *PLANE2 = (unsigned char*) PLANE2_ADDRESS;
    PLANE2[offset] = color;
	unsigned char *PLANE3 = (unsigned char*) PLANE3_ADDRESS;
    PLANE3[offset] = color;
}

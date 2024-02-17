#include "vga.h"
#include "../kernel/kernel.h"
#include "../memory/memory.h"
#include "../screen/screen.h"
#include "../common/stdlib.h"
#include "reg_ac.h"
#include "reg_crtc.h"
#include "reg_ext.h"
#include "reg_gc.h"
#include "reg_seq.h"
#include "vga_config.h"

#define COLOR_BLACK 0x0
#define COLOR_GREEN 0x2
#define COLOR_PURPLE 0xf


unsigned int vga_mode_var = 0;

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
	unsigned int saved_addr_reg = ioport_in(address);
    // Set the address to which we are writing
	ioport_out(address, index);
    // Set the value at that address by writing to the data port
	ioport_out(data, value);
    // Restore the original value of the address register
	ioport_out(address, saved_addr_reg);
}



void vga_info() {
	struct VGA vga;
	get_vga(vga);
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

#define VID_BACKUP_SRC 0xA0000
#define VID_BACKUP_DEST 0x0001a0000
#define VID_BACKUP_AMOUNT 0x1FFFF
void backup_vidmem() {
	// Save video memory somewhere else
	// 0xb8000 to 0xbffff (32K)
	// memcpy(0x0001a0000, 0xa0000, 0x1FFFF);
	unsigned char *vid_location = (unsigned char*) VID_BACKUP_SRC;
	unsigned char *backup_location = (unsigned char*) VID_BACKUP_DEST;
	for (u32 i=0; i < VID_BACKUP_AMOUNT; i++) {
    	*(backup_location+i) = *(vid_location+i);
	}
}
void restore_vidmem() {
	// Restore text-mode video memory
	// memcpy(0xa0000, 0x0001a0000, 0x1FFFF);
	unsigned char *vid_location = (unsigned char*) VID_BACKUP_SRC;
	unsigned char *backup_location = (unsigned char*) VID_BACKUP_DEST;
	for (u32 i=0; i < VID_BACKUP_AMOUNT; i++) {
    	*(vid_location+i) = *(backup_location+i);
	}
}
void turn_off_sequencer() {
	set_reg_seq(VGA_SEQ_REG_RESET, 0x1);
}
void turn_on_sequencer() {
	set_reg_seq(VGA_SEQ_REG_RESET, 0x3);
}

void vga_enter() {
	// Using mode 13h (320x200 linear 256-color mode) from:
	// https://wiki.osdev.org/VGA_Hardware#List_of_register_settings

	if (vga_mode_var == 1) return;
	vga_mode_var = 1;
    println("Attempting to switch modes...");

	struct AttributeController ac;
	get_ac(ac);
	ac.regAttributeMode = 0x41;
	ac.regOverscanColor = 0x00;
	ac.regColorPlane = 0x0F;
	ac.regHorizPixel = 0x00;
	ac.regPixelShift = 0x00;
	set_ac(ac);

	// this next bit will erase all the text mode fonts:
	// Mess w/ CRTC
	struct ExternalGeneral ext;
	get_ext(ext);
	ext.regMisc = 0x63;
	set_ext(ext);

	turn_off_sequencer();
	terrible_sleep_impl(500);
	backup_vidmem();
	// Work with sequencer
	struct Sequencer seq;
	get_seq(seq);
	set_reg_seq(VGA_SEQ_REG_CLOCKING, 0x01);
	set_reg_seq(VGA_SEQ_REG_MAP, 0x0F); // <--------------------- everything hinges on this!!!!!!!!!!!!!
	set_reg_seq(VGA_SEQ_REG_CHAR, 0x00);
	set_reg_seq(VGA_SEQ_REG_MEM, 0x0E);

	turn_on_sequencer();

	struct GraphicsController gc;
	get_gc(gc);
	gc.regGraphicsMode = 0x40;
	gc.regMisc = 0x05;
	set_gc(gc);

	u8 ioAddressSelect = 1; // assume color mode. // ext.regMisc & 0b1;
	struct CathodeRayTubeController crtc;
	get_crtc(crtc, ioAddressSelect);
	crtc.regHorizTotal = 0x5F;
	crtc.regEndHorizDisplay = 0x4F;
	crtc.regStartHorizBlanking = 0x50;
	crtc.regEndHorizBlanking = 0x82;
	crtc.regStartHorizRetrace = 0x54;
	crtc.regEndHorizRetrace = 0x80;
	crtc.regVertTotal = 0xBF;
	crtc.regOverflow = 0x1F;
	crtc.regPresetRowScan = 0x00;
	crtc.regMaxScanLine = 0x41;
	// crtc.regCursorStart = 0x00;
	// crtc.regCursorEnd = 0x00;
	// crtc.regStartAddressHigh = 0x00;
	// crtc.regStartAddressLow = 0x00;
	// crtc.regCursorLocationHigh = 0x00;
	// crtc.regCursorLocationLow = 0x00;
	crtc.regVertRetraceStart = 0x9C;
	crtc.regVertRetraceEnd = 0x8E;
	crtc.regVertDisplayEnd = 0x8F;
	crtc.regOffset = 0x28;
	crtc.regUnderlineLocation = 0x40;
	crtc.regStartVertBlanking = 0x96;
	crtc.regEndVertBlanking = 0xB9;
	crtc.regModeControl = 0xA3;
	// crtc.regLineCompare = 0xFF;
	set_crtc(crtc, ioAddressSelect);


	// memset(0xA0000, 0x0000, 0x1000);
	// memset(0xB0000, 0x0000, 0xFFFF);

	// draw_happy_face(0,0);

	// draw_happy_face(150,150);

	// draw_rectangle(100,100, 10, 10);
}

void vga_exit() {
	// Using mode 3h (80x25 text mode) from:
	// https://wiki.osdev.org/VGA_Hardware#List_of_register_settings
	
	if (vga_mode_var == 0) return;

	struct AttributeController ac;
	get_ac(ac);
	ac.regAttributeMode = 0x0C;
	ac.regOverscanColor = 0x00;
	ac.regColorPlane = 0x0F;
	ac.regHorizPixel = 0x08;
	ac.regPixelShift = 0x00;
	set_ac(ac);

	// this next bit will erase all the text mode fonts:
	// Mess w/ CRTC
	struct ExternalGeneral ext;
	get_ext(ext);
	ext.regMisc = 0x67;
	set_ext(ext);

	turn_off_sequencer();
	terrible_sleep_impl(500);
	restore_vidmem();
	// Work with sequencer
	struct Sequencer seq;
	get_seq(seq);
	// turn off sequencer
	set_reg_seq(VGA_SEQ_REG_RESET, 0x0);
	// sleep
	terrible_sleep_impl(1000);
	restore_vidmem();

	set_reg_seq(VGA_SEQ_REG_CLOCKING, 0x00);
	set_reg_seq(VGA_SEQ_REG_MAP, 0x0F); // <--------------------- everything hinges on this!!!!!!!!!!!!!
	set_reg_seq(VGA_SEQ_REG_CHAR, 0x00);
	set_reg_seq(VGA_SEQ_REG_MEM, 0x07);

	// turn on sequencer
	turn_on_sequencer();

	struct GraphicsController gc;
	get_gc(gc);
	set_reg_gc(VGA_GC_REG_GRAPHICSMODE, 0x10);
	set_reg_gc(VGA_GC_REG_MISC, 0x0E);

	u8 ioAddressSelect = 1; // assume color mode. // ext.regMisc & 0b1;
	struct CathodeRayTubeController crtc;
	get_crtc(crtc, ioAddressSelect);
	crtc.regHorizTotal = 0x5F;
	crtc.regEndHorizDisplay = 0x4F;
	crtc.regStartHorizBlanking = 0x50;
	crtc.regEndHorizBlanking = 0x82;
	crtc.regStartHorizRetrace = 0x55;
	crtc.regEndHorizRetrace = 0x81;
	crtc.regVertTotal = 0xBF;
	crtc.regOverflow = 0x1F;
	crtc.regPresetRowScan = 0x00;
	crtc.regMaxScanLine = 0x4F;
	// crtc.regCursorStart = 0x00;
	// crtc.regCursorEnd = 0x00;
	// crtc.regStartAddressHigh = 0x00;
	// crtc.regStartAddressLow = 0x00;
	// crtc.regCursorLocationHigh = 0x00;
	// crtc.regCursorLocationLow = 0x00;
	crtc.regVertRetraceStart = 0x9C;
	crtc.regVertRetraceEnd = 0x8E;
	crtc.regVertDisplayEnd = 0x8F;
	crtc.regOffset = 0x28;
	crtc.regUnderlineLocation = 0x1F;
	crtc.regStartVertBlanking = 0x96;
	crtc.regEndVertBlanking = 0xB9;
	crtc.regModeControl = 0xA3;
	// crtc.regLineCompare = 0xFF;
	set_crtc(crtc, ioAddressSelect);

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
	unsigned char *PLANE2 = (unsigned char*) 0xA0000;
    PLANE2[offset] = color;
}

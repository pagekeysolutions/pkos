#ifndef __VGA_REG_AC_H
#define __VGA_REG_AC_H

#include "../common/types.h"

// AC (Attribute Controller) Registers: http://www.osdever.net/FreeVGA/vga/attrreg.htm
struct AttributeController {
	u8 regPalettes[16]; 	// Palette Registers (0x0-0xF)
	u8 regAttributeMode; 	// Attribute Mode Control Register
    u8 regOverscanColor;    // Overscan Color Register
    u8 regColorPlane;       // Color Plane Enable Register
    u8 regHorizPixel;       // Horizontal Pixel Panning Register
    u8 regPixelShift;       // Pixel Shift Count Register
};
// Ports
#define VGA_AC_ADDR_PREREAD 0x3DA
#define VGA_AC_ADDR 0x3C0
#define VGA_AC_DATA 0x3C1
// Indices
#define VGA_AC_REG_PALETTE 	    0x00
#define VGA_AC_REG_ATTRIB       0x10
#define VGA_AC_REG_OVERSCAN     0x11
#define VGA_AC_REG_COLOR_PLANE  0x12
#define VGA_AC_REG_HORIZ_PIXEL  0x13
#define VGA_AC_REG_PIXEL_SHIFT  0x14

void set_ac(struct AttributeController *config);

void get_ac(struct AttributeController *config);

void print_ac(struct AttributeController config);

#endif

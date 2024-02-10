#ifndef __VGA_REG_CRTC_H
#define __VGA_REG_CRTC_H

#include "../common/types.h"

// CRTC (Cathode Ray Tube Controller): http://www.osdever.net/FreeVGA/vga/crtcreg.htm
struct CathodeRayTubeController {
	u8 regHorizTotal; 	// Horizontal Total Register
};
// Ports
#define VGA_CRTC_ADDR_MONO   0x3C0
#define VGA_CRTC_DATA_MONO  0x3C1
#define VGA_CRTC_ADDR_COLOR  0x3C0
#define VGA_CRTC_DATA_COLOR 0x3C1
// Indices
#define VGA_CRTC_REG_HORIZ_TOTAL 0x00

void set_crtc(struct CathodeRayTubeController config, u8 ioAddressSelect);

void get_crtc(struct CathodeRayTubeController config, u8 ioAddressSelect);

void print_crtc(struct CathodeRayTubeController config, u8 ioAddressSelect);

#endif

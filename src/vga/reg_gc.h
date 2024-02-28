#ifndef __VGA_REG_GC_H
#define __VGA_REG_GC_H

#include "../common/types.h"

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
// Ports
#define VGA_GC_ADDR 0x3CE
#define VGA_GC_DATA 0x3CF
// Indices
#define VGA_GC_REG_SR 				0x00
#define VGA_GC_REG_ENABLE_SR		0x01
#define VGA_GC_REG_COLORCOMPARE		0x02
#define VGA_GC_REG_DATAROTATE		0x03
#define VGA_GC_REG_READMAP			0x04
#define VGA_GC_REG_GRAPHICSMODE		0x05
#define VGA_GC_REG_MISC 			0x06
#define VGA_GC_REG_COLORDONTCARE	0x07
#define VGA_GC_REG_BITMASK			0x08

u32 get_reg_gc(u32 index);
u32 set_reg_gc(u32 index, u32 value);

void set_gc(struct GraphicsController config);

void get_gc(struct GraphicsController config);

void print_gc(struct GraphicsController config);

#endif

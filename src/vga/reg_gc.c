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


void set_graphics_controller(struct GraphicsController config) {

}

struct GraphicsController get_graphics_controller() {
    struct GraphicsController config;

    config.regSetReset = get_reg(VGA_GRAPHICS_ADDR, VGA_GRAPHICS_DATA, VGA_GRAPHICS_REG_SR);

    return config;
}

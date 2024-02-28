#ifndef __VGA_REG_CRTC_H
#define __VGA_REG_CRTC_H

#include "../common/types.h"

// CRTC (Cathode Ray Tube Controller): http:///www.osdever.net/FreeVGA/vga/crtcreg.htm
struct CathodeRayTubeController {
	u8 regHorizTotal; 	        // Horizontal Total Register
    u8 regEndHorizDisplay;      // End Horizontal Display Register
    u8 regStartHorizBlanking;   // Start Horizontal Blanking Register
    u8 regEndHorizBlanking;     // End Horizontal Blanking Register
    u8 regStartHorizRetrace;    // Start Horizontal Retrace Register
    u8 regEndHorizRetrace;      // End Horizontal Retrace Register
    u8 regVertTotal;            // Vertical Total Register
    u8 regOverflow;             // Overflow Register
    u8 regPresetRowScan;        // Preset Row Scan Register
    u8 regMaxScanLine;          // Maximum Scan Line Register
    u8 regCursorStart;          // Cursor Start Register
    u8 regCursorEnd;            // Cursor End Register
    u8 regStartAddressHigh;     // Start Address High Register
    u8 regStartAddressLow;      // Start Address Low Register
    u8 regCursorLocationHigh;   // Cursor Location High Register
    u8 regCursorLocationLow;    // Cursor Location Low Register
    u8 regVertRetraceStart;     // Vertical Retrace Start Register
    u8 regVertRetraceEnd;       // Vertical Retrace End Register
    u8 regVertDisplayEnd;       // Vertical Display End Register
    u8 regOffset;               // Offset Register
    u8 regUnderlineLocation;    // Underline Location Register
    u8 regStartVertBlanking;    // Start Vertical Blanking Register
    u8 regEndVertBlanking;      // End Vertical Blanking
    u8 regModeControl;          // CRTC Mode Control Reigster
    u8 regLineCompare;          // Line Compare Register
};
// Ports
#define VGA_CRTC_ADDR_MONO      0x3B4
#define VGA_CRTC_DATA_MONO      0x3B5
#define VGA_CRTC_ADDR_COLOR     0x3D4
#define VGA_CRTC_DATA_COLOR     0x3D5
// Indices
#define VGA_CRTC_REG_HORIZ_TOTAL            0x00
#define VGA_CRTC_REG_END_HORIZ_DISP         0x01
#define VGA_CRTC_REG_START_HORIZ_BLANKING   0x02
#define VGA_CRTC_REG_END_HORIZ_BLANKING     0x03
#define VGA_CRTC_REG_START_HORIZ_RETRACE    0x04
#define VGA_CRTC_REG_END_HORIZ_RETRACE      0x05
#define VGA_CRTC_REG_VERT_TOTAL             0x06
#define VGA_CRTC_REG_OVERFLOW               0x07
#define VGA_CRTC_REG_PRESET_ROW_SCAN        0x08
#define VGA_CRTC_REG_MAX_SCAN_LINE          0x09
#define VGA_CRTC_REG_CURSOR_START           0x0A
#define VGA_CRTC_REG_CURSOR_END             0x0B
#define VGA_CRTC_REG_START_ADDR_HIGH        0x0C
#define VGA_CRTC_REG_START_ADDR_LOW         0x0D
#define VGA_CRTC_REG_CURSOR_LOC_HIGH        0x0E
#define VGA_CRTC_REG_CURSOR_LOC_LOW         0x0F
#define VGA_CRTC_REG_VERT_RETRACE_START     0x10
#define VGA_CRTC_REG_VERT_RETRACE_END       0x11
#define VGA_CRTC_REG_VERT_DISPLAY_END       0x12
#define VGA_CRTC_REG_OFFSET                 0x13
#define VGA_CRTC_REG_UNDERLINE_LOCATION     0x14
#define VGA_CRTC_REG_START_VERT_BLANKING    0x15
#define VGA_CRTC_REG_END_VERT_BLANKING      0x16
#define VGA_CRTC_REG_MODE_CONTROL           0x17
#define VGA_CRTC_REG_LINE_COMPARE           0x18

u32 get_reg_crtc(u32 index, u8 ioAddressSelect);
u32 set_reg_crtc(u32 index, u32 value, u8 ioAddressSelect);

void set_crtc(struct CathodeRayTubeController config, u8 ioAddressSelect);

void get_crtc(struct CathodeRayTubeController config, u8 ioAddressSelect);

void print_crtc(struct CathodeRayTubeController config, u8 ioAddressSelect);

#endif

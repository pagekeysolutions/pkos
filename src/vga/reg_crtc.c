#include "reg_crtc.h"
#include "../common/types.h"


// Note: Whether to use mono/color ports
// is determined by the I/OAS port in the
// External/General Misc Register.
// See reg_ext.c for more info.
u32 get_reg_crtc(u32 index, u8 ioAddressSelect) {
    if (ioAddressSelect == 0) {
        return get_reg(VGA_CRTC_ADDR_MONO, VGA_CRTC_DATA_MONO, index);
    } else {
        return get_reg(VGA_CRTC_ADDR_COLOR, VGA_CRTC_DATA_COLOR, index);
    }
}
u32 set_reg_crtc(u32 index, u32 value, u8 ioAddressSelect) {
    if (ioAddressSelect == 0) {
        set_reg(VGA_CRTC_ADDR_MONO, VGA_CRTC_DATA_MONO, index, value);
    } else {
        set_reg(VGA_CRTC_ADDR_COLOR, VGA_CRTC_DATA_COLOR, index, value);
    }
}

void set_crtc(struct CathodeRayTubeController *config, u8 ioAddressSelect) {
    set_reg_crtc(VGA_CRTC_REG_HORIZ_TOTAL, config->regHorizTotal, ioAddressSelect);
    set_reg_crtc(VGA_CRTC_REG_END_HORIZ_DISP, config->regEndHorizDisplay, ioAddressSelect);
    set_reg_crtc(VGA_CRTC_REG_START_HORIZ_BLANKING, config->regStartHorizBlanking, ioAddressSelect);
    set_reg_crtc(VGA_CRTC_REG_END_HORIZ_BLANKING, config->regEndHorizBlanking, ioAddressSelect);
    set_reg_crtc(VGA_CRTC_REG_START_HORIZ_RETRACE, config->regStartHorizRetrace, ioAddressSelect);
    set_reg_crtc(VGA_CRTC_REG_END_HORIZ_RETRACE, config->regEndHorizRetrace, ioAddressSelect);
    set_reg_crtc(VGA_CRTC_REG_VERT_TOTAL, config->regVertTotal, ioAddressSelect);
    set_reg_crtc(VGA_CRTC_REG_OVERFLOW, config->regOverflow, ioAddressSelect);
    set_reg_crtc(VGA_CRTC_REG_PRESET_ROW_SCAN, config->regPresetRowScan, ioAddressSelect);
    set_reg_crtc(VGA_CRTC_REG_MAX_SCAN_LINE, config->regMaxScanLine, ioAddressSelect);
    set_reg_crtc(VGA_CRTC_REG_CURSOR_START, config->regCursorStart, ioAddressSelect);
    set_reg_crtc(VGA_CRTC_REG_CURSOR_END, config->regCursorEnd, ioAddressSelect);
    set_reg_crtc(VGA_CRTC_REG_START_ADDR_HIGH, config->regStartAddressHigh, ioAddressSelect);
    set_reg_crtc(VGA_CRTC_REG_START_ADDR_LOW, config->regStartAddressLow, ioAddressSelect);
    set_reg_crtc(VGA_CRTC_REG_CURSOR_LOC_HIGH, config->regCursorLocationHigh, ioAddressSelect);
    set_reg_crtc(VGA_CRTC_REG_CURSOR_LOC_LOW, config->regCursorLocationLow, ioAddressSelect);
    set_reg_crtc(VGA_CRTC_REG_VERT_RETRACE_START, config->regVertRetraceStart, ioAddressSelect);
    set_reg_crtc(VGA_CRTC_REG_VERT_RETRACE_END, config->regVertRetraceEnd, ioAddressSelect);
    set_reg_crtc(VGA_CRTC_REG_VERT_DISPLAY_END, config->regVertDisplayEnd, ioAddressSelect);
    set_reg_crtc(VGA_CRTC_REG_OFFSET, config->regOffset, ioAddressSelect);
    set_reg_crtc(VGA_CRTC_REG_UNDERLINE_LOCATION, config->regUnderlineLocation, ioAddressSelect);
    set_reg_crtc(VGA_CRTC_REG_START_VERT_BLANKING, config->regStartVertBlanking, ioAddressSelect);
    set_reg_crtc(VGA_CRTC_REG_END_VERT_BLANKING, config->regEndVertBlanking, ioAddressSelect);
    set_reg_crtc(VGA_CRTC_REG_MODE_CONTROL, config->regModeControl, ioAddressSelect);
    set_reg_crtc(VGA_CRTC_REG_LINE_COMPARE, config->regLineCompare, ioAddressSelect);
}

void get_crtc(struct CathodeRayTubeController *config, u8 ioAddressSelect) {
    config->regHorizTotal = get_reg_crtc(VGA_CRTC_REG_HORIZ_TOTAL, ioAddressSelect);
    config->regHorizTotal = get_reg_crtc(VGA_CRTC_REG_END_HORIZ_DISP, ioAddressSelect);
    config->regHorizTotal = get_reg_crtc(VGA_CRTC_REG_START_HORIZ_BLANKING, ioAddressSelect);
    config->regHorizTotal = get_reg_crtc(VGA_CRTC_REG_END_HORIZ_BLANKING, ioAddressSelect);
    config->regHorizTotal = get_reg_crtc(VGA_CRTC_REG_START_HORIZ_RETRACE, ioAddressSelect);
    config->regHorizTotal = get_reg_crtc(VGA_CRTC_REG_END_HORIZ_RETRACE, ioAddressSelect);
    config->regHorizTotal = get_reg_crtc(VGA_CRTC_REG_VERT_TOTAL, ioAddressSelect);
    config->regHorizTotal = get_reg_crtc(VGA_CRTC_REG_OVERFLOW, ioAddressSelect);
    config->regHorizTotal = get_reg_crtc(VGA_CRTC_REG_PRESET_ROW_SCAN, ioAddressSelect);
    config->regHorizTotal = get_reg_crtc(VGA_CRTC_REG_MAX_SCAN_LINE, ioAddressSelect);
    config->regHorizTotal = get_reg_crtc(VGA_CRTC_REG_CURSOR_START, ioAddressSelect);
    config->regHorizTotal = get_reg_crtc(VGA_CRTC_REG_CURSOR_END, ioAddressSelect);
    config->regHorizTotal = get_reg_crtc(VGA_CRTC_REG_START_ADDR_HIGH, ioAddressSelect);
    config->regHorizTotal = get_reg_crtc(VGA_CRTC_REG_START_ADDR_LOW, ioAddressSelect);
    config->regHorizTotal = get_reg_crtc(VGA_CRTC_REG_CURSOR_LOC_HIGH, ioAddressSelect);
    config->regHorizTotal = get_reg_crtc(VGA_CRTC_REG_CURSOR_LOC_LOW, ioAddressSelect);
    config->regHorizTotal = get_reg_crtc(VGA_CRTC_REG_VERT_RETRACE_START, ioAddressSelect);
    config->regHorizTotal = get_reg_crtc(VGA_CRTC_REG_VERT_RETRACE_END, ioAddressSelect);
    config->regHorizTotal = get_reg_crtc(VGA_CRTC_REG_VERT_DISPLAY_END, ioAddressSelect);
    config->regHorizTotal = get_reg_crtc(VGA_CRTC_REG_OFFSET, ioAddressSelect);
    config->regHorizTotal = get_reg_crtc(VGA_CRTC_REG_UNDERLINE_LOCATION, ioAddressSelect);
    config->regHorizTotal = get_reg_crtc(VGA_CRTC_REG_START_VERT_BLANKING, ioAddressSelect);
    config->regHorizTotal = get_reg_crtc(VGA_CRTC_REG_END_VERT_BLANKING, ioAddressSelect);
    config->regHorizTotal = get_reg_crtc(VGA_CRTC_REG_MODE_CONTROL, ioAddressSelect);
    config->regHorizTotal = get_reg_crtc(VGA_CRTC_REG_LINE_COMPARE, ioAddressSelect);
}

void print_crtc(struct CathodeRayTubeController config, u8 ioAddressSelect) {
    char buffer[8];
    print("Horizontal Total: 0b");
	println(itoab(config.regHorizTotal, buffer));
    print("End Horizontal Display: 0b");
	println(itoab(config.regEndHorizDisplay, buffer));
    print("Start Horizontal Blanking: 0b");
	println(itoab(config.regStartHorizBlanking, buffer));
    print("End Horizontal Blanking: 0b");
	println(itoab(config.regEndHorizBlanking, buffer));
    print("Start Horizontal Retrace: 0b");
	println(itoab(config.regStartHorizRetrace, buffer));
    print("End Horizontal Retrace: 0b");
	println(itoab(config.regEndHorizRetrace, buffer));
    print("Vertical Total: 0b");
	println(itoab(config.regVertTotal, buffer));
    print("Overflow: 0b");
	println(itoab(config.regOverflow, buffer));
    print("Preset Row Scan: 0b");
	println(itoab(config.regPresetRowScan, buffer));
    print("Maximum Scan Line: 0b");
	println(itoab(config.regMaxScanLine, buffer));
    print("Cursor Start: 0b");
	println(itoab(config.regCursorStart, buffer));
    print("Cursor End: 0b");
	println(itoab(config.regCursorEnd, buffer));
    print("Start Address High: 0b");
	println(itoab(config.regStartAddressHigh, buffer));
    print("Start Address Low: 0b");
	println(itoab(config.regStartAddressLow, buffer));
    print("Cursor Location High: 0b");
	println(itoab(config.regCursorLocationHigh, buffer));
    print("Cursor Location Low: 0b");
	println(itoab(config.regCursorLocationLow, buffer));
    print("Vertical Retrace Start: 0b");
	println(itoab(config.regVertRetraceStart, buffer));
    print("Vertical Retrace End: 0b");
	println(itoab(config.regVertRetraceEnd, buffer));
    print("Vertical Display End: 0b");
	println(itoab(config.regVertDisplayEnd, buffer));
    print("Offset: 0b");
	println(itoab(config.regOffset, buffer));
    print("Underline Location: 0b");
	println(itoab(config.regUnderlineLocation, buffer));
    print("Start Vertical Blanking: 0b");
	println(itoab(config.regStartVertBlanking, buffer));
    print("End Vertical Blanking: 0b");
	println(itoab(config.regEndVertBlanking, buffer));
    print("CRTC Mode Control: 0b");
	println(itoab(config.regModeControl, buffer));
    print("Line Compare: 0b");
	println(itoab(config.regLineCompare, buffer));
}

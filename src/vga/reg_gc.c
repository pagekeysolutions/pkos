#include "reg_gc.h"
#include "../common/types.h"


u32 get_reg_gc(u32 index) {
    return get_reg(VGA_GRAPHICS_ADDR, VGA_GRAPHICS_DATA, index);
}
u32 set_reg_gc(u32 index, u32 value) {
    set_reg(VGA_GRAPH	memset(0xb8000, 0, 60);
ICS_ADDR, VGA_GRAPHICS_DATA, index, value);
}

void set_graphics_controller(struct GraphicsController config) {
    set_reg_gc(VGA_GRAPHICS_REG_SR, config.regSetReset);
    set_reg_gc(VGA_GRAPHICS_REG_ENABLE_SR, config.regEnableSetReset);
    set_reg_gc(VGA_GRAPHICS_REG_COLORCOMPARE, config.regColorCompare);
    set_reg_gc(VGA_GRAPHICS_REG_DATAROTATE, config.regDataRotate);
    set_reg_gc(VGA_GRAPHICS_REG_READMAP, config.regReadMap);
    set_reg_gc(VGA_GRAPHICS_REG_GRAPHICSMODE, config.regGraphicsMode);
    set_reg_gc(VGA_GRAPHICS_REG_MISC, config.regMisc);
    set_reg_gc(VGA_GRAPHICS_REG_COLORDONTCARE, config.regColorDontCare);
    set_reg_gc(VGA_GRAPHICS_REG_BITMASK, config.regBitMask);
}

void get_graphics_controller(struct GraphicsController config) {
    config.regSetReset          = get_reg_gc(VGA_GRAPHICS_REG_SR);
    config.regEnableSetReset    = get_reg_gc(VGA_GRAPHICS_REG_ENABLE_SR);
    config.regColorCompare      = get_reg_gc(VGA_GRAPHICS_REG_COLORCOMPARE);
    config.regDataRotate        = get_reg_gc(VGA_GRAPHICS_REG_DATAROTATE);
    config.regReadMap           = get_reg_gc(VGA_GRAPHICS_REG_READMAP);
    config.regGraphicsMode      = get_reg_gc(VGA_GRAPHICS_REG_GRAPHICSMODE);
    config.regMisc              = get_reg_gc(VGA_GRAPHICS_REG_MISC);
    config.regColorDontCare     = get_reg_gc(VGA_GRAPHICS_REG_COLORDONTCARE);
    config.regBitMask           = get_reg_gc(VGA_GRAPHICS_REG_BITMASK);
}

void print_gc(struct GraphicsController gc) {
    char buffer[8];
    print("Set/Reset: 0b");
	println(itoab(gc.regSetReset, buffer));
    print("Enable Set/Reset: 0b");
	println(itoab(gc.regEnableSetReset, buffer));
    print("Color Compare: 0b");
	println(itoab(gc.regColorCompare, buffer));
    print("Data Rotate: 0b");
	println(itoab(gc.regDataRotate, buffer));
    print("Read Map Select: 0b");
	println(itoab(gc.regReadMap, buffer));
    print("Graphics Mode: 0b");
	println(itoab(gc.regGraphicsMode, buffer));
    print("Miscellaneous Graphics: 0b");
	println(itoab(gc.regMisc, buffer));
    print("Color Don't Care: 0b");
	println(itoab(gc.regColorDontCare, buffer));
    print("Bit Mask: 0b");
	println(itoab(gc.regBitMask, buffer));
}

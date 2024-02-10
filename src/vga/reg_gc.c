#include "reg_gc.h"
#include "../common/types.h"


u32 get_reg_gc(u32 index) {
    return get_reg(VGA_GC_ADDR, VGA_GC_DATA, index);
}
u32 set_reg_gc(u32 index, u32 value) {
    set_reg(VGA_GC_ADDR, VGA_GC_DATA, index, value);
}

void set_gc(struct GraphicsController config) {
    set_reg_gc(VGA_GC_REG_SR, config.regSetReset);
    set_reg_gc(VGA_GC_REG_ENABLE_SR, config.regEnableSetReset);
    set_reg_gc(VGA_GC_REG_COLORCOMPARE, config.regColorCompare);
    set_reg_gc(VGA_GC_REG_DATAROTATE, config.regDataRotate);
    set_reg_gc(VGA_GC_REG_READMAP, config.regReadMap);
    set_reg_gc(VGA_GC_REG_GRAPHICSMODE, config.regGraphicsMode);
    set_reg_gc(VGA_GC_REG_MISC, config.regMisc);
    set_reg_gc(VGA_GC_REG_COLORDONTCARE, config.regColorDontCare);
    set_reg_gc(VGA_GC_REG_BITMASK, config.regBitMask);
}

void get_gc(struct GraphicsController config) {
    config.regSetReset          = get_reg_gc(VGA_GC_REG_SR);
    config.regEnableSetReset    = get_reg_gc(VGA_GC_REG_ENABLE_SR);
    config.regColorCompare      = get_reg_gc(VGA_GC_REG_COLORCOMPARE);
    config.regDataRotate        = get_reg_gc(VGA_GC_REG_DATAROTATE);
    config.regReadMap           = get_reg_gc(VGA_GC_REG_READMAP);
    config.regGraphicsMode      = get_reg_gc(VGA_GC_REG_GRAPHICSMODE);
    config.regMisc              = get_reg_gc(VGA_GC_REG_MISC);
    config.regColorDontCare     = get_reg_gc(VGA_GC_REG_COLORDONTCARE);
    config.regBitMask           = get_reg_gc(VGA_GC_REG_BITMASK);
}

void print_gc(struct GraphicsController config) {
    char buffer[8];
    print("Set/Reset: 0b");
	println(itoab(config.regSetReset, buffer));
    print("Enable Set/Reset: 0b");
	println(itoab(config.regEnableSetReset, buffer));
    print("Color Compare: 0b");
	println(itoab(config.regColorCompare, buffer));
    print("Data Rotate: 0b");
	println(itoab(config.regDataRotate, buffer));
    print("Read Map Select: 0b");
	println(itoab(config.regReadMap, buffer));
    print("Graphics Mode: 0b");
	println(itoab(config.regGraphicsMode, buffer));
    print("Miscellaneous Graphics: 0b");
	println(itoab(config.regMisc, buffer));
    print("Color Don't Care: 0b");
	println(itoab(config.regColorDontCare, buffer));
    print("Bit Mask: 0b");
	println(itoab(config.regBitMask, buffer));
}

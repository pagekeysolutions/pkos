#include "reg_ac.h"
#include "../common/types.h"


u32 get_reg_ac(u32 index) {
    return get_reg(VGA_AC_ADDR, VGA_AC_DATA, index);
}
u32 set_reg_ac(u32 index, u32 value) {
    set_reg(VGA_AC_ADDR, VGA_AC_DATA, index, value);
}

void set_ac(struct AttributeController config) {
    for (u8 i = 0; i < 16; i++) {
        set_reg_ac(VGA_AC_REG_PALETTE, config.regPalettes[i]);
    }
    set_reg_ac(VGA_AC_REG_ATTRIB, config.regAttributeMode);
    set_reg_ac(VGA_AC_REG_OVERSCAN, config.regOverscanColor);
    set_reg_ac(VGA_AC_REG_COLOR_PLANE, config.regColorPlane);
    set_reg_ac(VGA_AC_REG_HORIZ_PIXEL, config.regHorizPixel);
    set_reg_ac(VGA_AC_REG_PIXEL_SHIFT, config.regPixelShift);
}

void get_ac(struct AttributeController config) {
    for (u8 i = 0; i < 16; i++) {
        config.regPalettes[i] = get_reg_ac(VGA_AC_REG_PALETTE + i);
    }
    config.regAttributeMode = get_reg_gc(VGA_AC_REG_ATTRIB);
    config.regOverscanColor = get_reg_gc(VGA_AC_REG_OVERSCAN);
    config.regColorPlane    = get_reg_gc(VGA_AC_REG_COLOR_PLANE);
    config.regHorizPixel    = get_reg_gc(VGA_AC_REG_HORIZ_PIXEL);
    config.regPixelShift    = get_reg_gc(VGA_AC_REG_PIXEL_SHIFT);
}

void print_ac(struct AttributeController ac) {
    char buffer[8];
    for (u8 i = 0; i < 16; i++) {
        print("Palette ");
        print(itoa(i));
        print(": 0b");
        println(itoab(ac.regPalettes[i], buffer));
    }
    print("Attribute Mode Control: 0b");
	println(itoab(ac.regAttributeMode, buffer));
    print("Overscan Color: 0b");
	println(itoab(ac.regOverscanColor, buffer));
    print("Color Plane Enable: 0b");
	println(itoab(ac.regColorPlane, buffer));
    print("Horizontal Pixel Panning: 0b");
	println(itoab(ac.regHorizPixel, buffer));
    print("Pixel Shift Count: 0b");
	println(itoab(ac.regPixelShift, buffer));
}

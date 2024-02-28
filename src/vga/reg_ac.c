#include "reg_ac.h"
#include "../common/types.h"

// Palette Address Source
// Set to 1 unless loading colors
#define PAS_BIT 0b100000

u32 get_reg_ac(u32 index) {
    return get_reg(VGA_AC_ADDR | PAS_BIT, VGA_AC_DATA, index);
}
u32 set_reg_ac(u32 index, u32 value) {\
    // Before trying to read the AC address, read 0x3DA
    // to force the 0x3C0 register into the address state
    get_reg(VGA_AC_ADDR_PREREAD);
    set_reg(VGA_AC_ADDR | PAS_BIT, VGA_AC_DATA, index, value);
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
    for (u8 i = 0; i < 15; i++) {
        config.regPalettes[i] = get_reg_ac(VGA_AC_REG_PALETTE + i);
    }
    config.regAttributeMode = get_reg_gc(VGA_AC_REG_ATTRIB);
    config.regOverscanColor = get_reg_gc(VGA_AC_REG_OVERSCAN);
    config.regColorPlane    = get_reg_gc(VGA_AC_REG_COLOR_PLANE);
    config.regHorizPixel    = get_reg_gc(VGA_AC_REG_HORIZ_PIXEL);
    config.regPixelShift    = get_reg_gc(VGA_AC_REG_PIXEL_SHIFT);
}

void print_ac(struct AttributeController config) {
    char buffer[8];
    for (u8 i = 0; i < 16; i++) {
        print("Palette ");
        print(itoa(i));
        print(": 0b");
        println(itoab(config.regPalettes[i], buffer));
    }
    print("Attribute Mode Control: 0b");
	println(itoab(config.regAttributeMode, buffer));
    print("Overscan Color: 0b");
	println(itoab(config.regOverscanColor, buffer));
    print("Color Plane Enable: 0b");
	println(itoab(config.regColorPlane, buffer));
    print("Horizontal Pixel Panning: 0b");
	println(itoab(config.regHorizPixel, buffer));
    print("Pixel Shift Count: 0b");
	println(itoab(config.regPixelShift, buffer));
}

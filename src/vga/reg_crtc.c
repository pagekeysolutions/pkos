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

void set_crtc(struct CathodeRayTubeController config, u8 ioAddressSelect) {
    // TODO
}

void get_crtc(struct CathodeRayTubeController config, u8 ioAddressSelect) {
    // TODO
    config.regMisc = ioport_in(VGA_MISC_IN);
}

void print_crtc(struct CathodeRayTubeController config, u8 ioAddressSelect) {
    // TODO
    char buffer[8];
    print("Miscellaneous Output: 0b");
	println(itoab(config.regMisc, buffer));
}

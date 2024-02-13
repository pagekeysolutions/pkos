#include "reg_ext.h"
#include "../common/types.h"


void set_ext(struct ExternalGeneral config) {
    ioport_out(VGA_MISC_OUT, config.regMisc);
    u8 ioAddressSelect = config.regMisc & 0b1;
    /**
     * The docs say that when this is 0,
     * you need to use the "mono" addresses provided.
     * When set to 1, use the "color" address.
     * Feature Control Register and Input Status #1 Register
     * both specify separate addresses for mono/color
     * However, Input Status #0 and #1 are both read-only.
    */
    if (ioAddressSelect == 0) {
        // Mono
        ioport_out(VGA_FEAT_OUT_MONO, config.regFeature);
    } else {
        // Color
        ioport_out(VGA_FEAT_OUT_COLOR, config.regFeature);
    }
}

void get_ext(struct ExternalGeneral config) {
    config.regMisc = ioport_in(VGA_MISC_IN);
    config.regFeature = ioport_in(VGA_FEAT_IN);

    config.regInputStatus0 = ioport_in(VGA_INPUT_STATUS_0_IN);
    u8 ioAddressSelect = config.regMisc & 0b1;
    if (ioAddressSelect == 0) {
        config.regInputStatus1 = ioport_in(VGA_INPUT_STATUS_1_IN_MONO);
    } else {
        config.regInputStatus1 = ioport_in(VGA_INPUT_STATUS_1_IN_COLOR);
    }
}

void print_ext(struct ExternalGeneral config) {
    char buffer[8];
    print("Miscellaneous Output: 0b");
	println(itoab(config.regMisc, buffer));
    print("Feature Control: 0b");
	println(itoab(config.regFeature, buffer));
    print("Input Status #0: 0b");
	println(itoab(config.regInputStatus0, buffer));
    print("Input Status #1: 0b");
	println(itoab(config.regInputStatus1, buffer));
}

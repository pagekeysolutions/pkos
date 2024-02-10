#include "reg_ext.h"
#include "../common/types.h"


void set_ext(struct ExternalGeneral config) {
    ioport_out(VGA_MISC_OUT, config.regMisc);
}

void get_ext(struct ExternalGeneral config) {
    config.regMisc = ioport_in(VGA_MISC_IN);
    config.regFeature = ioport_in(VGA_FEAT_IN);
    config.regInputStatus0 = ioport_in(VGA_INPUT_STATUS_0_IN);
    config.regInputStatus1 = ioport_in(VGA_INPUT_STATUS_1_IN);
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

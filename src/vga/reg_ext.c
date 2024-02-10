#include "reg_ext.h"
#include "../common/types.h"


void set_ext(struct ExternalGeneral config) {
    ioport_out(VGA_MISC_OUT, config.regMisc);
}

void get_ext(struct ExternalGeneral config) {
    config.regMisc = ioport_in(VGA_MISC_IN);
}

void print_ext(struct ExternalGeneral config) {
    char buffer[8];
    print("Miscellaneous Output: 0b");
	println(itoab(config.regMisc, buffer));
}

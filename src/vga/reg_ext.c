#include "reg_ext.h"
#include "../common/types.h"


u32 get_reg_ext(u32 index) {
    return get_reg(VGA_GC_ADDR, VGA_GC_DATA, index);
}
u32 set_reg_ext(u32 index, u32 value) {
    set_reg(VGA_GC_ADDR, VGA_GC_DATA, index, value);
}

void set_ext(struct ExternalGeneral config) {
    set_reg_gc(VGA_GC_REG_SR, config.regSetReset);
}

void get_ext(struct ExternalGeneral config) {
    config.regSetReset          = get_reg_gc(VGA_GC_REG_SR);
}

void print_ext(struct ExternalGeneral config) {
    char buffer[8];
    print("Set/Reset: 0b");
	println(itoab(gc.regSetReset, buffer));
}

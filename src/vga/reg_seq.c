#include "reg_seq.h"
#include "../common/types.h"


u32 get_reg_seq(u32 index) {
    return get_reg(VGA_SEQ_ADDR, VGA_SEQ_DATA, index);
}
u32 set_reg_seq(u32 index, u32 value) {
    set_reg(VGA_SEQ_ADDR, VGA_SEQ_DATA, index, value);
}

void set_seq(struct Sequencer config) {
    set_reg_seq(VGA_SEQ_REG_RESET, config.regReset);
    // set_reg_seq(VGA_SEQ_REG_CLOCKING, config.regClocking);
    // set_reg_seq(VGA_SEQ_REG_MAP, config.regMapMask);
    set_reg_seq(VGA_SEQ_REG_CHAR, config.regCharMapSelect);
    set_reg_seq(VGA_SEQ_REG_MEM, config.regSeqMemoryMode);
}

void get_seq(struct Sequencer config) {
    config.regReset = get_reg_seq(VGA_SEQ_REG_RESET);
    config.regClocking = get_reg_seq(VGA_SEQ_REG_CLOCKING);
    config.regMapMask = get_reg_seq(VGA_SEQ_REG_MAP);
    config.regCharMapSelect = get_reg_seq(VGA_SEQ_REG_CHAR);
    config.regSeqMemoryMode = get_reg_seq(VGA_SEQ_REG_MEM);
}

void print_seq(struct Sequencer config) {
    char buffer[8];
    print("Reset: 0b");
	println(itoab(config.regReset, buffer));
    print("Clocking Mode: 0b");
	println(itoab(config.regClocking, buffer));
    print("Map Mask: 0b");
	println(itoab(config.regMapMask, buffer));
    print("Character Map Select: 0b");
	println(itoab(config.regCharMapSelect, buffer));
    print("Sequencer Memory Mode: 0b");
	println(itoab(config.regSeqMemoryMode, buffer));
}

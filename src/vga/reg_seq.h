#ifndef __VGA_REG_SEQ_H
#define __VGA_REG_SEQ_H

#include "../common/types.h"

// SEQ (Sequencer) Registers: http://www.osdever.net/FreeVGA/vga/seqreg.htm
struct Sequencer {
	u8 regReset; 	        // Reset Register
    u8 regClocking;         // Clocking Mode Register
    u8 regMapMask;          // Map Mask Register
    u8 regCharMapSelect;    // Character Map Select Register
    u8 regSeqMemoryMode;    // Sequencer Memory Mode Register
};
// Ports
#define VGA_SEQ_ADDR 0x3C4
#define VGA_SEQ_DATA 0x3C5
// Indices
#define VGA_SEQ_REG_RESET       0x00 // Reset Register
#define VGA_SEQ_REG_CLOCKING    0x01 // Clocking Mode Register
#define VGA_SEQ_REG_MAP         0x02 // Map Mask Register
#define VGA_SEQ_REG_CHAR        0x03 // Character Map Select Register
#define VGA_SEQ_REG_MEM         0x04 // Sequencer Memory Mode Register

u32 get_reg_seq(u32 index);
u32 set_reg_seq(u32 index, u32 value);

void set_seq(struct Sequencer *config);

void get_seq(struct Sequencer *config);

void print_seq(struct Sequencer config);

#endif

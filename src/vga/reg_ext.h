#ifndef __VGA_REG_EXT_H
#define __VGA_REG_EXT_H

#include "../common/types.h"

// EXT (External/General) Registers: http://www.osdever.net/FreeVGA/vga/extreg.htm
struct ExternalGeneral {
    u8 regMisc;         // Miscellaneous Output Register
    u8 regFeature;      // Feature Control Register
    u8 regInputStatus0; // Input Status #0 Register
    u8 regInputStatus1; // Input Status #1 Register
};
// Ports
#define VGA_MISC_IN             0x3CC // Miscellaneous Output Register (read)
#define VGA_MISC_OUT            0x3C2 // Miscellaneous Output Register (write)
#define VGA_FEAT_IN             0x3CA // Feature Control Register (read)
#define VGA_FEAT_OUT_MONO       0x3BA // Feature Control Register (write, mono)
#define VGA_FEAT_OUT_COLOR      0x3DA // Feature Control Register (write, color)
#define VGA_INPUT_STATUS_0_IN   0x3C2 // Input Status #0 Register (read-only)
#define VGA_INPUT_STATUS_1_IN_MONO   0x3BA // Input Status #1 Register (read-only, MONO)
#define VGA_INPUT_STATUS_1_IN_COLOR  0x3DA // Input Status #1 Register (read-only, COLOR)

void set_ext(struct ExternalGeneral config);

void get_ext(struct ExternalGeneral config);

void print_ext(struct ExternalGeneral config);

#endif

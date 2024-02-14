#ifndef __VGA_CONFIG_H
#define __VGA_CONFIG_H

#include "../common/types.h"
#include "reg_ac.h"
#include "reg_crtc.h"
#include "reg_ext.h"
#include "reg_gc.h"
#include "reg_seq.h"


struct VGA {
    struct AttributeController ac;
    struct CathodeRayTubeController crtc;
    struct ExternalGeneral ext;
    struct GraphicsController gc;
    struct Sequencer seq;
};

void set_vga(struct VGA config);

struct VGA get_vga(struct VGA config);

void print_vga(struct VGA config);

#endif

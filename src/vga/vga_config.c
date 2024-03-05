#include "../common/types.h"
#include "vga_config.h"


void set_vga(struct VGA *config) {
    set_ac(&(config->ac));
    set_ext(&(config->ext));
    u8 ioAddressSelect = config->ext.regMisc & 0b1;
    set_crtc( (&(config->crtc)), ioAddressSelect);
    set_gc(&(config->gc));
    // set_seq(config->seq);
}

struct VGA get_vga(struct VGA *config) {
    get_ac(&(config->ac));
    get_ext(&(config->ext));
    u8 ioAddressSelect = config->ext.regMisc & 0b1;
    get_crtc( (&(config->crtc)), ioAddressSelect);
    get_gc(&(config->gc));
    get_seq(&(config->seq));
}

void print_vga(struct VGA config) {
    println("Attribute Controller:");
    print_ac(config.ac);
    println("External/General:");
    print_ext(config.ext);
    u8 ioAddressSelect = config.ext.regMisc & 0b1;
    println("CRTC:");
    print_crtc(config.crtc, ioAddressSelect);
    println("Graphics Controller:");
    print_gc(config.gc);
    println("Sequencer:");
    print_seq(config.seq);
}

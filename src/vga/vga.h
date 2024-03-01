#ifndef __VGA_H
#define __VGA_H

#include "../common/types.h"

// Advice for accessing VGA registers: http://www.osdever.net/FreeVGA/vga/vgareg.htm

// VGA Text Mode Info: http://www.osdever.net/FreeVGA/vga/vgatext.htm

#define VGA_ADDRESS 0xB8000
#define REGION0 0xA0000
#define REGION1 0xA0000
#define REGION2 0xB0000
#define REGION3 0xB8000

#define VGA_MEM_ADDR        REGION0

#define	VGA_AC_INDEX		0x3C0
#define	VGA_AC_WRITE		0x3C0
#define	VGA_AC_READ		    0x3C1
#define	VGA_INSTAT_READ		0x3DA
#define	VGA_MISC_WRITE		0x3C2
#define	VGA_MISC_READ		0x3CC

/*			                COLOR emulation	 MONO emulation */
#define VGA_CRTC_INDEX		0x3D4		     /* 0x3B4 */
#define VGA_CRTC_DATA		0x3D5		     /* 0x3B5 */
#define VGA_GC_INDEX 		0x3CE
#define VGA_GC_DATA 		0x3CF
#define VGA_SEQ_INDEX		0x3C4
#define VGA_SEQ_DATA		0x3C5

#define VGA_PALETTE_MASK    0x3C6
#define VGA_PALETTE_READ    0x3C7
#define VGA_PALETTE_WRITE   0x3C8
#define VGA_PALETTE_DATA    0x3C9

#define	VGA_NUM_AC_REGS		21
#define	VGA_NUM_CRTC_REGS	25
#define	VGA_NUM_GC_REGS		9
#define	VGA_NUM_SEQ_REGS	5

#define VGA_SCREEN_WIDTH    320
#define VGA_SCREEN_HEIGHT   200
#define VGA_SCREEN_SIZE     320 * 200

#define COLOR(_r, _g, _b)((uint8_t)( \
    (((_r) & 0x7) << 5) |       \
    (((_g) & 0x7) << 2) |       \
    (((_b) & 0x3) << 0)))

#define COLOR_R(_index) (((_index) >> 5) & 0x7)
#define COLOR_G(_index) (((_index) >> 2) & 0x7)
#define COLOR_B(_index) (((_index) >> 0) & 0x3)

/* need to add CLAMP, this macro is currently unused */
#define COLOR_ADD(_index, _d) __extension__({   \
        __typeof__(_index) _c = (_index);       \
        __typeof__(_d) __d = (_d);              \
        COLOR(                                  \
            CLAMP(COLOR_R(_c) + __d, 0, 7),     \
            CLAMP(COLOR_G(_c) + __d, 0, 7),     \
            CLAMP(COLOR_B(_c) + __d, 0, 3)      \
        );})

#define VALUE_TO_COLOR(_value) COLOR(           \
    (((_value) >> 5) & 0x7),                    \
    (((_value) >> 2) & 0x7),                    \
    ((_value) & 0x3))             



u32 get_reg(u32 address, u32 data, u32 index);
u32 set_reg(u32 address, u32 data, u32 index, u32 value);

void vga_info();
void vga_font();
void vga_enter();
void vga_exit();

void vga_clear_screen();
void vga_plot_pixel(u32 x, u32 y, u32 color);

void draw_happy_face(int x, int y);
void draw_rectangle(int x, int y, int width, int height, int color);

#endif
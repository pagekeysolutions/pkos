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

u32 get_reg(u32 address, u32 data, u32 index);
u32 set_reg(u32 address, u32 data, u32 index, u32 value);

void vga_info();
void vga_font();
void vga_enter();
void vga_exit();

void vga_clear_screen();
void vga_plot_pixel(int x, int y, unsigned short color);

void draw_happy_face(int x, int y);
void draw_rectangle(int x, int y, int width, int height, int color);

#endif
#ifndef __VGA_H
#define __VGA_H

#define VGA_ADDRESS 0xB8000
#define PLANE0_ADDRESS 0xA0000
#define PLANE1_ADDRESS 0xA0000
#define PLANE2_ADDRESS 0xB0000
#define PLANE3_ADDRESS 0xB8000

void vga_info();
void vga_enter();
void vga_exit();

void vga_clear_screen();
void vga_plot_pixel(int x, int y, unsigned short color);

void draw_happy_face(int x, int y);
void draw_rectangle(int x, int y, int width, int height);

#endif
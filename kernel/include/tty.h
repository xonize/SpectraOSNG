#ifndef _KERNEL_TTY_H
#define _KERNEL_TTY_H

#include <stddef.h>
#include <stdint.h>

void screen_init(void* addr, uint32_t width, uint32_t height, uint32_t pitch, uint8_t bpp, uint8_t colormode);
void screen_draw_img(char* data, uint32_t x, uint32_t y);
void screen_put_pixel(uint32_t x, uint32_t y, uint32_t color);
void screen_put_char(unsigned short int c, uint32_t cx, uint32_t cy, uint32_t fg, uint32_t bg);
void screen_write_string(const char* data, uint32_t x, uint32_t y, uint32_t fg, uint32_t bg);
#endif

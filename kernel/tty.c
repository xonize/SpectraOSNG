#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
// #include <string.h>
#include <include/logo.h>
#include <tty.h>

static uint32_t WIDTH = 1280;
static uint32_t HEIGHT = 720;
static uint8_t DEPTH = 24;
static size_t ATTRIBUTE = 7;
static uint32_t PITCH; // number of bytes that are in each row on screen
static uint8_t FBTYPE; // color type/mode of framebuffer
static uint32_t s_color; // default color
static volatile void* fb;


void screen_init(void* addr, uint32_t width, uint32_t height, uint32_t pitch, uint8_t bpp, uint8_t colormode) {
    fb = addr;
    WIDTH = width;
    HEIGHT = height;
    PITCH = pitch;
    DEPTH = bpp;
    FBTYPE = colormode;
    s_color = 0xffffff;
}


void screen_draw_img(char* data, uint32_t x, uint32_t y) {
    char pixel[4];
    for (uint32_t yy=0;yy<logo_height;yy++) {
        for (uint32_t xx=0;xx<logo_width;xx++) {
            HEADER_PIXEL(data, pixel);
            pixel[3] = 0;
            uint32_t num = (uint32_t) pixel[0] << 24 |
                (uint32_t)pixel[1] << 16 |
                (uint32_t)pixel[2] << 8  |
                (uint32_t)pixel[3];
            screen_put_pixel(x+xx, y+yy, num);
        }
    }
}

void screen_put_pixel(uint32_t x, uint32_t y, uint32_t color) {
    uint32_t* pixel = fb + calculate_offset(x, y);
    *pixel = (color & 0xffffff) | (*pixel & 0xff000000);
}
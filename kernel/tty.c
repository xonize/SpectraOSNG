#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
// #include <string.h>
#include <kernel/psf.h>
#include <logo.h>
#include <tty.h>

static uint32_t WIDTH = 1280;
static uint32_t HEIGHT = 720;
static uint8_t DEPTH = 24;
static size_t ATTRIBUTE = 7;
static uint32_t PITCH; // number of bytes that are in each row on screen
static uint8_t FBTYPE; // color type/mode of framebuffer
static uint32_t s_color; // default color
static volatile char* fb;

extern char _binary_font_psf_start[];

int calculate_offset(int x, int y);


void screen_init(void* addr, uint32_t width, uint32_t height, uint32_t pitch, uint8_t bpp, uint8_t colormode) {
    fb = (char*) addr;
    WIDTH = width;
    HEIGHT = height;
    PITCH = pitch;
    DEPTH = bpp;
    FBTYPE = colormode;
    s_color = 0xffffff;
}


void screen_draw_img(char* data, uint32_t x, uint32_t y) {
    uint32_t pixel[4];
    for (uint32_t yy=0;yy<logo_height;yy++) {
        for (uint32_t xx=0;xx<logo_width;xx++) {
            HEADER_PIXEL(data, pixel);
            // 0 = Red, 1 = Green, 2 = Blue
            pixel[3] = 0;
            // Num 
            uint32_t num = (uint32_t) pixel[0] << 16 |
                (uint32_t)pixel[1] << 8 |
                (uint32_t)pixel[2];
                // (uint32_t)pixel[3];
            screen_put_pixel(x+xx, y+yy, num);
        }
    }
}

void screen_put_pixel(uint32_t x, uint32_t y, uint32_t color) {
    uint32_t* pixel = fb + calculate_offset(x, y);
    *pixel = color;
}

int calculate_offset(int x, int y) {
    return (x * DEPTH/8) + y * PITCH;
}

void screen_put_char(unsigned short int c, uint32_t cx, uint32_t cy, uint32_t fg, uint32_t bg) {
    #define PIXEL uint32_t
    // FONT IS V1 NOT V2!!! EZ CLAP
    PSF_font *font = (PSF_font*)&_binary_font_psf_start;
    int bytesperline = (font->width + 7) / 8;

    // get character glyph, if non-existent use first glyph
    unsigned char *glyph = (unsigned char*)&_binary_font_psf_start + font->headersize + (c>0&&c<font->numglyph?c:0)*font->bytesperglyph;
    // calculate upper left corner on screen. only happens once, offset adjusted later which is faster
    int offset = (cy * font->height * PITCH) + (cx * (font->width + 1) * sizeof(PIXEL));
    // int offset = 16;

    // display pixels according to bitmap
    int xx, yy, line, mask;
    for (yy=0;yy<font->height;yy++) {
        // save starting pos of line
        line = offset;
        mask = 1<<(font->width-1);
        // display row
        for (xx=0;xx<font->width;xx++) {
            *((PIXEL*)(fb+line)) = *((unsigned int*)glyph) & mask ? fg : bg;
            // adjust to next pixel
            mask >>= 1;
            line += sizeof(PIXEL);
        }
        glyph += bytesperline;
        offset += PITCH;
    }
    #undef PIXEL
}

void screen_write_string(const char* data, uint32_t x, uint32_t y, uint32_t fg, uint32_t bg) {
    for (int i = 0;data[i]!=0;i++,x++) {
        screen_put_char(data[i], x, y, fg, bg);
    }
}
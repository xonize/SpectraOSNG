#include <stdint.h>
#include <cpuid.h>
#include <stddef.h>
#include <limine.h>
#include <tty.h>
#include <kernel/test.h>
#include <logo.h>
#include <arch/x86_64/gdt.h>
#include <arch/x86_64/idt.h>
#include <qemu/output.h>
#include <string.h>

// The Limine requests can be placed anywhere, but it is important that
// the compiler does not optimise them away, so, usually, they should
// be made volatile or equivalent.

static volatile struct limine_framebuffer_request framebuffer_request = {
    .id = LIMINE_FRAMEBUFFER_REQUEST,
    .revision = 0
};

// Halt and catch fire function.
static void hcf(void) {
    asm ("cli");
    for (;;) {
        asm ("hlt");
    }
}

int isLongMode(void) {
    int rdx, unused;
    __cpuid(1, unused, unused, unused, rdx);
    return rdx & bit_LM;
}

// The following will be our kernel's entry point.
// If renaming _start() to something else, make sure to change the
// linker script accordingly.
void _start(void) {
    // dont need to check for long mode because limine protocol does it automatically

    // Ensure we got a framebuffer.
    if (framebuffer_request.response == NULL
     || framebuffer_request.response->framebuffer_count < 1) {
        hcf();
    }
    FlushGDT();
    init_idt();

    // Fetch the first framebuffer.
    struct limine_framebuffer *framebuffer = framebuffer_request.response->framebuffers[0];

    // Note: we assume the framebuffer model is RGB with 32-bit pixels.
    // if (HELLO) {
    //     for (size_t i = 0; i < 100; i++) {
    //     uint32_t *fb_ptr = framebuffer->address;
    //     fb_ptr[i * (framebuffer->pitch / 4) + i] = 0xffffff;
    // }
    // }
    screen_init(framebuffer->address, framebuffer->width, framebuffer->height, framebuffer->pitch, framebuffer->bpp, 0); // type wtf?!
    screen_draw_img(logo_header_data, 920, 508);                    // this seems to work in pixels
    screen_write_string("SpectraOS", 82, 24, 0xffffff, 0x000000);   // but this works in characters or something similar. why?
    set_up_serial_port();
    qemu_puts("Booted.");

    // We're done, just hang...
    hcf();
}
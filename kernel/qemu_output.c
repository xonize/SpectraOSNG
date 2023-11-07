#include <qemu/output.h>
#include <stdint.h>

void set_up_serial_port(void) {
    outb(0x3F8 + 1, 0x00);
    outb(0x3F8 + 3, 0x80);
    outb(0x3F8 + 0, 0x03);
    outb(0x3F8 + 1, 0x00);
    outb(0x3F8 + 3, 0x03);
    outb(0x3F8 + 2, 0xC7);
    outb(0x3F8 + 4, 0x0B);
}

void wait_empty_transmission(void) {
    while ((inb(0x3F8 + 5) & 0x20) == 0) {;}
}

void qemu_put_char(char character) {
    wait_empty_transmission();
    outb(0x3F8, character);
}

void qemu_puts(char* text) {
    for (uint32_t i=0; text[i]!=0; i++) {
        qemu_put_char(text[i]);
    }
}

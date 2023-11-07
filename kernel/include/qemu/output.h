#ifndef _KERNEL_QEMU_OUTPUT_H
#define _KERNEL_QEMU_OUTPUT_H

#include <serial/serial.h>

void set_up_serial_port(void);
void wait_empty_transmission(void);
void qemu_put_char(char character);
void qemu_puts(char* text);

#endif
#ifndef SPECTRAOS_SERIAL_H_
#define SPECTRAOS_SERIAL_H_

#include <stdint.h>

uint32_t inbl(uint16_t port);
void outbl(uint16_t port, uint32_t data);
void outbw(uint16_t port, uint16_t data);
uint16_t inbw(uint16_t port);
void outb(uint16_t port, uint8_t data);
uint8_t inb(uint16_t port);
void delay(uint32_t microseconds);

#endif
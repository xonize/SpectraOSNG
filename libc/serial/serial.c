#include <serial/serial.h>

void delay(uint32_t microseconds) {
    for (uint32_t i = 0; i < microseconds; ++i) {
        inb(0x80);
    }
}

uint32_t inbl(uint16_t port) {
    uint32_t result;
    asm volatile("inl %%dx, %%eax" : "=a"(result) : "dN"(port));
    return result;
}

void outbl(uint16_t port, uint32_t data) {
    asm volatile("outl %%eax, %%dx" : : "dN"(port), "a"(data));
}

void outbw(uint16_t port, uint16_t data) {
    asm volatile("outw %0, %1" : : "a"(data), "Nd"(port));
}

uint16_t inbw(uint16_t port) {
    uint16_t result;
    asm volatile("inw %1, %0" : "=a"(result) : "Nd"(port));
    return result;
}

void outb(uint16_t port, uint8_t data) {
    asm volatile("outb %0, %1" : : "a"(data), "Nd"(port));
}

uint8_t inb(uint16_t port) {
    uint8_t result;
    asm volatile("inb %1, %0" : "=a"(result) : "Nd"(port));
    return result;
}
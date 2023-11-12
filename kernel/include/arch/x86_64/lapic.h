#ifndef X86_64_LAPIC_H_
#define X86_64_LAPIC_H_
#include <stdint.h>

void init_lapic();

uint32_t read_apic_register(uint32_t register_offset);
void write_apic_register(uint32_t register_offset, uint32_t value);

#endif
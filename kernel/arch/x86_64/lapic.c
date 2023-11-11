#include <arch/x86_64/lapic.h>
#include <kernel/asm_wrappers.h>

uint32_t get_lapic_addr(void) {
    uint64_t msr_val = rdmsr(0x1B);
    return (uint32_t)((msr_val >> 12) & 0b11111111111111111111); // get bits 12-31 - addr
}
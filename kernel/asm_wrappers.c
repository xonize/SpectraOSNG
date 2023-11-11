#include <kernel/asm_wrappers.h>

uint64_t rdmsr(uint64_t msr) {
    uint32_t low, high;
    asm volatile ("rdmsr" : "=a"(low), "=d"(high) : "c"(msr));

    return ((uint64_t)high << 32) | low;
}
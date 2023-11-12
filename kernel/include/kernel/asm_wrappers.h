#ifndef _KERNEL_ASM_WRAPPERS_H
#define _KERNEL_ASM_WRAPPERS_H

#include <stdint.h>

uint64_t rdmsr(uint64_t msr);
void wrmsr(uint64_t msr, uint64_t value);
#endif
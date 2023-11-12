#ifndef _KERNEL_MEM_UTIL_H
#define _KERNEL_MEM_UTIL_H
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

#define READMEM32(addr) \
(*(volatile uint32_t*)((uintptr_t)addr))

#define READMEM64(addr) \
(*(volatile uint64_t*)((uintptr_t)addr))

#define WRITEMEM32(addr, u32) \
(*(volatile uint32_t*)((uintptr_t)addr)) = u32

#define WRITEMEM64(addr, u64) \
(*(volatile uint64_t*)((uintptr_t)addr)) = u64


#endif
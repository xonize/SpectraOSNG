#include <arch/x86_64/gdt.h>
#include <stdint.h>

uint64_t gdtEntries[7] = {
    0, // 0x00 null selector
    0x00AF9B000000FFFF, //0x08 kernel code
    0x00AF93000000FFFF, //0x10 kernel data
    0x00AFF3000000FFFF, //0x18 user data
    0x00AFFB000000FFFF, //0x20 user code
    0, //0x28 tss low
    0, //0x30 tss high
};

typedef struct __attribute__((aligned (8))) __attribute__((__packed__)) gdtr{
    uint16_t limit;
    uint64_t base;
} gdtr;

gdtr g = {sizeof(uint64_t) * 7 - 1, (uintptr_t)gdtEntries};

void FlushGDT() {
    asm volatile("lgdt %0" :: "m"(g));

    asm volatile("mov %0, %%ax;  \
        mov %%ax, %%ds; \
        mov %%ax, %%ss; \
        mov %%ax, %%es; \
        mov %%ax, %%fs; \
        pop %%rdi; \
        push %1; \
        push %%rdi; \
        lretq " 
        :: "g"(KernelDataSelector), "g"(KernelCodeSelector)
        : "rdi"
    );
}


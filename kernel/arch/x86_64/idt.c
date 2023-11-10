#include <stdint.h>
#include <tty.h>
#include <serial/serial.h>
#include <qemu/output.h>
#include <stdlib.h>
#include <arch/x86_64/pic.h>

struct interrupt_descriptor {
    uint16_t address_low;
    uint16_t selector;
    uint8_t ist;
    uint8_t flags;
    uint16_t address_mid;
    uint32_t address_high;
    uint32_t reserved;
} __attribute__((packed));

struct idtr {
    uint16_t limit;
    uint64_t base;
} __attribute__((packed));

struct cpu_status_t
{
    uint64_t r15;
    uint64_t r14;
    uint64_t r13;
    uint64_t r12;
    uint64_t r11;
    uint64_t r10;
    uint64_t r9;
    uint64_t r8;
    
    uint64_t gs;
    uint64_t fs;

    uint64_t rsi;
    uint64_t rdi;
    uint64_t rbp;
    uint64_t rdx;
    uint64_t rcx;
    uint64_t rbx;
    uint64_t rax;

    uint64_t vector_number;
    uint64_t error_code;
    
    uint64_t iret_rip;
    uint64_t iret_cs;
    uint64_t iret_flags;
    uint64_t iret_rsp;
    uint64_t iret_ss;
};


struct interrupt_descriptor idt[256];

void set_idt_entry(uint8_t vector, void* handler, uint8_t dpl) {
    uint64_t handler_addr = (uint64_t)handler;

    struct interrupt_descriptor* entry = &idt[vector];
    entry->address_low = handler_addr & 0xFFFF;
    entry->address_mid = (handler_addr >> 16) & 0xFFFF;
    entry->address_high = handler_addr >> 32;
    entry->selector = 0x8;
    //trap gate + present + DPL
    entry->flags = 0b1110 | ((dpl & 0b11) << 5) |(1 << 7);
    //ist disabled
    entry->ist = 0;
}

void load_idt(void* idt_addr) {
    struct idtr idt_reg;
    idt_reg.limit = 0xFFF;
    idt_reg.base = (uint64_t)idt_addr;
    asm volatile("lidt %0" :: "m"(idt_reg));
}

void init_idt() {
    extern char vector_0_handler[];
    for (int i = 0; i < 19; i++) {
        // calculates positions in memory based on offset from vector_0 because all are consecutive aligned to 16
        set_idt_entry(i, (uint64_t)vector_0_handler + (i * 16), 0);
    }
    load_idt(&idt);
}

void interrupt_dispatch(struct cpu_status_t* context) {
    // TODO: implement qemu serial output on interrupt
    // also fix comp error
    const char* interrupt_number;
    // itoa(context->vector_number, interrupt_number, 10);
    qemu_puts("Received Interrupt");
    // qemu_puts(interrupt_number);
    qemu_puts("\n");
    switch (context->vector_number) {
        case 0:
            break;
        case 1:
            break;
        case 2:
            break;
        case 3:
            break;
        case 4:
            break;
        case 5:
            break;
        case 6:
            break;
        case 7:
            break;
        case 8:
            break;
        case 9:
            break;
        case 10:
            break;
        case 11:
            break;
        case 12:
            break;
        case 13:
            break;
        case 14:
            break;
        case 16:
            break;
        case 17:
            break;
        case 18:
            break;
        case 19:
            break;
        default:
            break;
    }

    if (context->vector_number >= 8) {
        outb(PIC_COMMAND_SLAVE, PIC_EOI);
    }
    outb(PIC_COMMAND_MASTER, PIC_EOI);
    return context;
}
#include <stdint.h>
#include <tty.h>


extern char vector_0_handler[];
extern char vector_1_handler[];

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
    //other pushed registers
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

#define V "vector_"
#define H "_handler"
#define IDTExpansion(n) "vector_" #n "_handler"

void init_idt() {
    // todo: change i in loop
    for (int i = 0; i < 2; i++){
        set_idt_entry(i, (uint64_t)IDTExpansion(i) + (i * 16), 0);
    }
    load_idt(&idt);
}

void interrupt_dispatch(struct cpu_status_t* context)
{
    switch (context->vector_number)
    {
        case 13:
            screen_put_pixel(10, 10, 0xff0000);
            break;
        case 14:
            screen_put_pixel(10, 10, 0x00ff00);
            break;
        default:
            screen_put_pixel(10, 10, 0x0000ff);
            break;
    }
    return context;
}
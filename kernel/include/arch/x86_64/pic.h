#ifndef X86_64_APIC_H_
#define X86_64_APIC_H_

// Constants for PIC
#define PIC_COMMAND_MASTER 0x20
#define PIC_DATA_MASTER 0x21
#define PIC_COMMAND_SLAVE 0xA0
#define PIC_DATA_SLAVE 0xA1

#define PIC_MASTER_OFFSET 0x20
#define PIC_SLAVE_OFFSET 0x28

// Initialization Command Words
#define ICW_1 0x11
#define PIC_MODE_8086 0x01

#define PIC_EOI 0x20



// void remap_pic(void);
// void mask_pic(void);
void disable_pic(void);

#endif
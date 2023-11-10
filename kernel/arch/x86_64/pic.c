#include <arch/x86_64/pic.h>
#include <stdint.h>
#include <serial/serial.h>

void remap_pic(void) {
    uint8_t mask1 = inb(PIC_DATA_MASTER);
    uint8_t mask2 = inb(PIC_DATA_SLAVE);
    outb(PIC_COMMAND_MASTER, ICW_1);
    outb(PIC_COMMAND_SLAVE, ICW_1);
    outb(PIC_DATA_MASTER, PIC_MASTER_OFFSET);
    outb(PIC_DATA_SLAVE, PIC_SLAVE_OFFSET);
    outb(PIC_DATA_MASTER, 0x04); // Slave PIC at IQR2?
    outb(PIC_DATA_SLAVE, 0x02); // Cascade indentity?
    outb(PIC_DATA_MASTER, PIC_MODE_8086);
    outb(PIC_DATA_SLAVE, PIC_MODE_8086);
    outb(PIC_DATA_MASTER, mask1);
    outb(PIC_DATA_SLAVE, mask2);
}
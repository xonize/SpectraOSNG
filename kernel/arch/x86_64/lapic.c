#include <arch/x86_64/lapic.h>
#include <kernel/asm_wrappers.h>
#include <arch/x86_64/pic.h>
#include <kernel/kernel.h>
#include <cpuid.h>
#include <stdbool.h>
#include <qemu/output.h>
#include <kernel/mem/vmm_util.h>

uint32_t lapic_base_addr;
uint64_t lapic_hh_base_addr;
bool in_x2_mode;


void init_lapic() {
    disable_pic();
    uint64_t msr_val = rdmsr(0x1B);
    lapic_base_addr = (uint64_t)((msr_val >> 12) & 0b11111111111111111111); // get bits 12-31 - addr
    lapic_hh_base_addr = lapic_base_addr + kernel_settings.hhdm_offset;

    // find if x2apic is available. it is cpuid leaf 1, ecx bit 21
    uint32_t ignored;
    uint32_t x_apic_leaf = 0;
    uint32_t x2_apic_leaf = 0;
    __get_cpuid(1, &ignored, &ignored, &x2_apic_leaf, &x_apic_leaf);
    (void)ignored;

    if (x2_apic_leaf & (1 << 21)) {
        // X2Apic is available.
        qemu_puts("X2APIC AVAILABLE and enabled \n");
        kernel_settings.use_x2_apic = true;
        in_x2_mode = true;

        // apic will be accessed by MSRs so no need to map MMIO regs
        msr_val |= (1<<10);
        wrmsr(0x1B, msr_val);
    } else if (x_apic_leaf & (1 << 9)) {
        qemu_puts("APIC available\n");
        kernel_settings.use_x2_apic = false;
        in_x2_mode = false;
        // regs are accessed by MMIO so need to map them
        // TODO: map regs - is this necessary with Limine? or can we just add hhdm offset?
    } else {
        kernel_settings.use_x2_apic = false;
        qemu_puts("No APIC supported.\n");
        return; // Not good
    }

    uint32_t spurious_interrupt_register = read_apic_register(0xF0); // APIC spurious vector register offset

    // enable apic
    write_apic_register(0xF0, (1<<8) & 255); // Software enable | spurious interrupt idt location

    uint32_t version_register = read_apic_register(0x30); // APIC version register offset
}


uint32_t read_apic_register(uint32_t register_offset) {
    if (in_x2_mode) {
        return (uint32_t)rdmsr((register_offset >> 4) + 0x800);
    } else {
        return READMEM32(lapic_hh_base_addr + register_offset);
    }
}

void write_apic_register(uint32_t register_offset, uint32_t value) {
    if (in_x2_mode) {
        wrmsr((register_offset >> 4) + 0x800, value);
    } else {
        WRITEMEM32(lapic_hh_base_addr + register_offset, value);
    }
}
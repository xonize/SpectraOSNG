#ifndef _KERNEL_H
#define _KERNEL_H
#include <stdint.h>
#include <stdbool.h>

struct keyboard_status_t {
    uint8_t scancode_set;
    bool translation_enabled;
};

typedef struct kernel_settings_t {
    struct keyboard_status_t keyboard;
    uint64_t hhdm_offset;
    uint64_t kernel_uptime;
    bool use_x2_apic;
} kernel_settings_t;

extern kernel_settings_t kernel_settings;

#endif
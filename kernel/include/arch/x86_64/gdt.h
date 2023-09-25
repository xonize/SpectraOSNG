#include <stdint.h>

#ifndef X86_64_GDT_H_
#define X86_64_GDT_H_

const uint16_t KernelCodeSelector = 0x08 | 0;
const uint16_t KernelDataSelector = 0x10 | 0;
const uint16_t UserDataSelector   = 0x18 | 3;
const uint16_t UserCodeSelector   = 0x20 | 3;
const uint16_t TssSelector        = 0x28;

void FlushGDT();

#endif
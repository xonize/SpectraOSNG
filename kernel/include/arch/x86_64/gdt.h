#include <stdint.h>

#ifndef X86_64_GDT_H_
#define X86_64_GDT_H_

extern uint16_t KernelCodeSelector;
extern uint16_t KernelDataSelector;
extern uint16_t UserDataSelector;
extern uint16_t UserCodeSelector;
extern uint16_t TssSelector;

void FlushGDT();

#endif
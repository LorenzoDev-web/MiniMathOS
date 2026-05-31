#include "../include/types.h"
#include "idt.h"

IDTEntry idt[256];
IDTPointer idt_ptr;

void idt_set_gate(int n, u32 handler) {

    idt[n].offset_low =
        handler & 0xFFFF;

    idt[n].selector = 0x08;

    idt[n].zero = 0;

    idt[n].type_attr = 0x8E;

    idt[n].offset_high =
        (handler >> 16) & 0xFFFF;
}

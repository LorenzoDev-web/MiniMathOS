// idt.c Header

#ifndef IDT_H
#define IDT_H

#include "../include/types.h"

typedef struct {

    u16 offset_low;
    u16 selector;
    u8 zero;
    u8 type_attr;
    u16 offset_high;

} __attribute__((packed)) IDTEntry;

typedef struct {

    u16 limit;
    u32 base;

} __attribute__((packed)) IDTPointer;

void idt_init();

#endif

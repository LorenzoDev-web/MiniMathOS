#include "io.h"

u8 inb(u16 port) {

    u8 result;

    __asm__ volatile(
        "inb %1, %0"
        : "=a"(result)
        : "Nd"(port)
    );

    return result;
}

void outb(u16 port, u8 value) {

    __asm__ volatile (
        "outb %%al, %%dx"
        :
        : "a"(value), "d"(port)
    );
}

void outw(u16 port, u16 value) {

    __asm__ volatile (
        "outw %%ax, %%dx"
        :
        : "a"(value), "d"(port)
    );
}

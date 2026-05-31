#include "../include/types.h"
#include "../drivers/io.h"
#include "../drivers/vga.h"

#include "idt.h"
#include "panic.h"
#include "../include/globals.h"

void sleep() {

    int i;

    for (i = 0; i < 900000000; i++) {

        __asm__ volatile("nop");
    }
}


void reboot() {

    u8 good = 0x02;

    while (good & 0x02)
        good = inb(0x64);

    outb(0x64, 0xFE);

    volatile int i;

    for (i = 0; i < 30000000; i++) {
        __asm__ volatile("nop");
    }

    IDTPointer null_idt;

    null_idt.limit = 0;
    null_idt.base = 0;

    __asm__ volatile("lidt %0" : : "m"(null_idt));

    __asm__ volatile("int $3");

    for (;;)
        __asm__ volatile("hlt");
}


/*==========================*/
/* PANIC */
/*==========================*/

__attribute__((noreturn))
void panic(const char* s) {

    color = 0x1F;

    clear();

    y = 10;

    print_center("KERNEL PANIC");

    y += 2;

    print_center((char*)s);

    y += 2;


    sleep();

    outw(0x604, 0x2000);
    reboot();

    for (;;) {

        __asm__ volatile("cli; hlt");
    }
}

/*
* Kernel critical routines.
*
* Implements:
* - sleep(): simple delay via busy wait.
* - reboot(): system reboot via keyboard controller.
* - panic(): handling of fatal kernel errors.
*
* In case of unrecoverable failure, panic() displays an error
* message on the screen, attempts to restart the machine, and,
* if that is not possible, permanently halts CPU execution.
*/

/*
* Rotinas críticas do kernel.
*
* Implementa:
* - sleep() : atraso simples por espera ocupada (busy wait).
* - reboot() : reinicialização do sistema via controlador de teclado.
* - panic() : tratamento de erros fatais do kernel.
*
* Em caso de falha irrecuperável, panic() exibe uma mensagem
* de erro na tela, tenta reiniciar a máquina e, caso isso não
* seja possível, interrompe permanentemente a execução da CPU.
*/

/*
* Kernel critical routines.
*
* Implements:
* - sleep(): simple delay via busy wait.
* - reboot(): system reboot via keyboard controller.
* - panic(): handling of fatal kernel errors.
*
* In case of unrecoverable failure, panic() displays an error
* message on the screen, attempts to restart the machine, and,
* if that is not possible, permanently halts CPU execution.
*/

/*
* Rotinas críticas do kernel.
*
* Implementa:
* - sleep() : atraso simples por espera ocupada (busy wait).
* - reboot() : reinicialização do sistema via controlador de teclado.
* - panic() : tratamento de erros fatais do kernel.
*
* Em caso de falha irrecuperável, panic() exibe uma mensagem
* de erro na tela, tenta reiniciar a máquina e, caso isso não
* seja possível, interrompe permanentemente a execução da CPU.
*/

#include "../include/types.h"
#include "../drivers/io.h"
#include "../drivers/vga.h"

#include "idt.h"
#include "panic.h"
#include "../include/globals.h"



void sleep() {

    int i;

    for (i = 0; i < 2000000000; i++) {

        __asm__ volatile("nop");
    }
}


void reboot() {

    u8 good = 0x02;

    while (good & 0x02)
        good = inb(0x64);

    outb(0x64, 0xFE);

    volatile int i;

    for (i = 0; i < 20000000; i++) {
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

    u32 *ebp;

    __asm__ volatile("mov %%ebp, %0" : "=r"(ebp));

    print("Stack Trace:\n");

    for (int i = 0; i < 10 && ebp; i++) {
        print_hex(ebp[1]);
        print("\n");
        ebp = (u32*)ebp[0];
    }


    sleep();

    outw(0x604, 0x2000);
    reboot();

    for (;;) {

        __asm__ volatile("cli; hlt");
    }
}

int panic_ready() {
    return 1;
}




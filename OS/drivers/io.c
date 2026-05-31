/*
* Routines for accessing I/O ports of the x86 architecture.
*
* inb() - Reads 1 byte from a hardware port.
* outb() - Writes 1 byte to a hardware port.
* outw() - Writes 2 bytes (16 bits) to a hardware port.
*
* These functions use inline assembly to execute the CPU's
* IN and OUT instructions, allowing the kernel to communicate
* directly with hardware devices such as the keyboard, PIC, PIT, and serial ports.
*/

/*
* Rotinas de acesso a portas de E/S (I/O Ports) da arquitetura x86.
*
* inb() - Lê 1 byte de uma porta de hardware.
* outb() - Escreve 1 byte em uma porta de hardware.
* outw() - Escreve 2 bytes (16 bits) em uma porta de hardware.
*
* Essas funções utilizam assembly inline para executar as instruções
* IN e OUT da CPU, permitindo que o kernel se comunique diretamente
* com dispositivos de hardware como teclado, PIC, PIT e portas seriais.
*/

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

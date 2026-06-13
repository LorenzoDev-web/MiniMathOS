/*
* Management of the Interrupt Descriptor Table (IDT).
*
* The IDT is a structure used by the CPU to locate
* the handlers of interrupts and exceptions.
*
* This module allows configuring table entries,
* associating interrupt vectors with kernel functions.
*
* Each entry contains the handler's address, the code
* segment selector, and the access attributes required
* by the processor.
*/

/*
* Gerenciamento da Interrupt Descriptor Table (IDT).
*
* A IDT é uma estrutura utilizada pela CPU para localizar
* os tratadores (handlers) de interrupções e exceções.
*
* Este módulo permite configurar entradas da tabela,
* associando vetores de interrupção a funções do kernel.
*
* Cada entrada contém o endereço do handler, o seletor
* de segmento de código e os atributos de acesso exigidos
* pelo processador.
*/

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

int idt_ready() {
    return 1;
}

// Main Function of the system
// Função principal do sistema

/* Kernel Core */
/* Núcleo do Kernel*/

#include "../drivers/vga.h"
#include "../drivers/io.h"
#include "../drivers/keyboard.h"
#include "panic.h"
#include "idt.h"
#include "draw.h"

extern void keyboard_poll();

#define GUARD 0xDEADBEEF
#define HEAP_BASE 0x100000

uint8_t* heap_start;
uint8_t* heap_end;
uint8_t* heap_current;

/* Heap Corruption verificator*/

typedef struct block {
    size_t size;
    struct block* next;
    uint32_t magic_start;
} heap_block_t;

typedef struct {
    heap_block_t* first;
} heap_t;

heap_t heap;

typedef struct {
    uint32_t magic_end;
} footer_t;

void heap_init()
{
    heap_start = (uint8_t*)HEAP_BASE;
}


void heap_check()
{
    heap_block_t* b = heap.first;

    while (b) {

        if (b->magic_start != GUARD)
            panic("HEAP CORRUPTION: header damaged");

        footer_t* f = (footer_t*)((char*)(b + 1) + b->size);

        if (f->magic_end != GUARD)
            panic("HEAP CORRUPTION: footer damaged");

        b = b->next;
    }
}




void kernel_main() {


    verify_err();
    verify_pass();
    ksleep(7);



    clear();

    heap_check();


    print("Mini Math OS\n");
    print("> ");

    while (1) {
        keyboard_poll();
    }

}

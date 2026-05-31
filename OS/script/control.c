#include "../types.h"

extern u8 inb(u16 port);
extern int stop_program;


void check_escape() {

    if (inb(0x64) & 1) {

        u8 scancode = inb(0x60);

        if (scancode == 1) {

            stop_program = 1;
        }
    }
}

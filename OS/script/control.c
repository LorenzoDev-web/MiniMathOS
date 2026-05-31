/*
* Monitoring of the Escape key.
*
* Checks the PS/2 keyboard controller and detects when
* the Esc key is pressed. When this occurs, the global
* variable stop_program is set, allowing the interruption
* of running programs or loops.
*/

/*
* Monitoramento da tecla Escape.
*
* Verifica o controlador de teclado PS/2 e detecta quando
* a tecla Esc é pressionada. Quando isso ocorre, a variável
* global stop_program é definida, permitindo interromper
* a execução de programas ou loops em andamento.
*/

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

#include "../types.h"
#include "../include/types.h"
#include "../include/globals.h"
#include "../drivers/vga.h"
#include "../shell/shell.h"

extern int shift;


/* ========================= */
/* KEYBOARD */
/* ========================= */


void handle_key(char c) {

    if (!c)
        return;

    if (editing) {

        if (c == 27) {

            editing = 0;

            print("\n\nEXIT EDITOR");
            print("\n> ");

            return;
        }

        if (c == '\b') {

            if (prog_len > 0) {

                prog_len--;

                putc('\b');
            }

            return;
        }

        if (prog_len < 4095) {

            program[prog_len++] = c;

            putc(c);
        }

        return;
    }

    if (c == '\n') {

        shell();
        return;
    }

    if (c == '\b') {

        if (input_len > 0) {

            input_len--;

            putc('\b');
        }

        return;
    }

    if (input_len < 255) {

        input[input_len++] = c;

        putc(c);
    }
}




char keyboard_map[128] = {

    0,
    27,

    '1','2','3','4','5','6','7','8','9','0',
    '-','=',
    '\b',
    '\t',

    'q','w','e','r','t','y','u','i','o','p',
    '[',']',
    '\n',

    0,

    'a','s','d','f','g','h','j','k','l',
    ';','\'','`',

    0,

    '\\',

    'z','x','c','v','b','n','m',
    ',', '.', '/',

    0,
    '*',

    0,

    ' ',
};

char shift_keyboard_map[128] = {

    0,
    27,

    '!','@','#','$','%','^','&','*','(',')',
    '_','+',

    '\b',
    '\t',

    'Q','W','E','R','T','Y','U','I','O','P',
    '{','}',
    '\n',

    0,

    'A','S','D','F','G','H','J','K','L',
    ':','"','~',

    0,

    '|',

    'Z','X','C','V','B','N','M',
    '<','>','?',

    0,
    '*',

    0,

    ' ',
};

extern int shift;

extern char keyboard_map[128];
extern char shift_keyboard_map[128];

extern u8 inb(u16 port);
extern void handle_key(char c);

void keyboard_poll() {

    if (inb(0x64) & 1) {

        u8 scancode = inb(0x60);

        if (
            scancode == 42 ||
            scancode == 54
        ) {

            shift = 1;
        }

        else if (
            scancode == 170 ||
            scancode == 182
        ) {

            shift = 0;
        }

        else if (!(scancode & 0x80)) {

            char c;

            if (scancode < 128) {

                if (shift)
                    c = shift_keyboard_map[scancode];
                else
                    c = keyboard_map[scancode];

                handle_key(c);
            }
        }
    }
}

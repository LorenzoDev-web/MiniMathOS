/*
* VGA Text Mode Driver.
*
* Implements text output to the VGA buffer (0xB8000),
* including writing characters, strings, numbers,
* screen clearing, cursor control, and scrolling.
*/

/*
* Driver VGA Text Mode.
*
* Implementa saída de texto para o buffer VGA (0xB8000),
* incluindo escrita de caracteres, strings, números,
* limpeza de tela, controle de cursor e scroll.
*/

#include "../include/types.h"
#include "vga.h"
#include "../include/globals.h"


/* ========================= */
/* VGA TEXT */
/* ========================= */

volatile u16* video = (u16*)0xB8000;


void plot(int px, int py, char c) {

    if (px < 0 || px >= 80)
        return;

    if (py < 0 || py >= 25)
        return;

    video[py * 80 + px] =
        (color << 8) | (u8)c;
}

void clear() {

    int i;

    for (i = 0; i < 80 * 25; i++) {

        video[i] =
            (color << 8) | ' ';
    }

    x = 0;
    y = 0;
}

/* ========================= */
/* TEXT */
/* ========================= */

void scroll() {

    int row;
    int col;

    if (y < 25)
        return;

    for (row = 1; row < 25; row++) {

        for (col = 0; col < 80; col++) {

            video[(row - 1) * 80 + col] =
                video[row * 80 + col];
        }
    }

    for (col = 0; col < 80; col++) {

        video[24 * 80 + col] =
            (color << 8) | ' ';
    }

    y = 24;
}

void putc(char c) {

    if (c == '\n') {

        x = 0;
        y++;

        scroll();

        return;
    }

    if (c == '\r') {

        x = 0;
        return;
    }

    if (c == '\b') {

        if (x > 0) {

            x--;

            video[y * 80 + x] =
                (color << 8) | ' ';
        }

        return;
    }

    if (x >= 80) {

        x = 0;
        y++;

        scroll();
    }

    video[y * 80 + x] =
        (color << 8) | (u8)c;

    x++;
}

void print(char* s) {

    while (*s)
        putc(*s++);
}

int strlen(char* s) {

    int len = 0;

    while (s[len])
        len++;

    return len;
}

void print_center(char* s) {

    int len = strlen(s);

    x = (80 - len) / 2;

    print(s);

    y++;
    x = 0;
}

void print_int(int n) {

    char buf[16];

    int i = 0;

    if (n == 0) {

        putc('0');
        return;
    }

    if (n < 0) {

        putc('-');
        n = -n;
    }

    while (n > 0) {

        buf[i++] =
            '0' + (n % 10);

        n /= 10;
    }

    while (i > 0)
        putc(buf[--i]);
}

void print_float(float f) {

    if (f < 0) {

        putc('-');
        f = -f;
    }

    int integer = (int)f;

    float frac_f = f - (float)integer;

    int frac = (int)(frac_f * 100.0f + 0.5f);

    print_int(integer);

    putc('.');

    if (frac < 10)
        putc('0');

    print_int(frac);
}

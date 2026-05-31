// Global Variables Header
// Header de Variáveis Globais

#ifndef GLOBALS_H
#define GLOBALS_H

#include "types.h"
#include "../script/runtime.h"

extern char program[4096];
extern int prog_len;

extern int stop_program;

extern unsigned char color;

extern int x;
extern int y;

extern int label_count;

extern int loop_count;

extern int editing;

extern char input[256];
extern int input_len;

#endif

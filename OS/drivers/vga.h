// VGA.c Header

#ifndef VGA_H
#define VGA_H

#include "../include/types.h"
#include "stdint.h"

extern int x;
extern int y;
extern u8 color;

void clear();
void putc(char c);
void print(const char* s);
void plot(int px,int py,char c);
void print_center(char* s);
void print_int(int n);
void print_hex(uint32_t value);
void print_reg(const char* name, uint32_t value);
void shell();

#endif

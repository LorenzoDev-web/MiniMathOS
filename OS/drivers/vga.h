#ifndef VGA_H
#define VGA_H

#include "../include/types.h"

extern int x;
extern int y;
extern u8 color;

void clear();
void putc(char c);
void print(char* s);
void plot(int px,int py,char c);
void print_center(char* s);
void print_int(int n);
void shell();

#endif

// io.c Header

#ifndef IO_H
#define IO_H

#include "../include/types.h"

u8 inb(u16 port);
void outb(u16 port, u8 value);
void outw(u16 port, u16 value);

#endif

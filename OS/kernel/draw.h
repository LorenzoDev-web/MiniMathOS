// draw.c Header

#ifndef DRAW_H
#define DRAW_H

void ksleep(unsigned int ticks);
void draw_progress(void);
void module_ok(const char* name);
void module_loading(const char* name);
void module_fail(const char* name);
void verify_err(void);
void verify_pass(void);

#endif

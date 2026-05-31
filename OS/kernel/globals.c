#include "../include/types.h"

int editing = 0;

char input[256];
int input_len = 0;

char program[4096];
int prog_len = 0;

int stop_program = 0;

unsigned char color = 0x0F;

int x = 0;
int y = 0;
int shift = 0;

/* LABELS */

typedef struct {
    char name[32];
    int pos;
} Label;

Label labels[32];
int label_count = 0;

/* LOOPS */

typedef struct {
    char var[32];

    float current;
    float end;
    float step;

    int pos;
} ForLoop;

ForLoop loops[16];
int loop_count = 0;

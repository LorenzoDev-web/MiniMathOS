#ifndef RUNTIME_H
#define RUNTIME_H

typedef struct {

    char name[32];
    float value;

} NumVar;

typedef struct {

    char name[32];
    int pos;

} Label;

typedef struct {

    char var[32];

    float current;
    float end;
    float step;

    int pos;

} ForLoop;

extern NumVar num_vars[64];
extern int num_var_count;

extern Label labels[32];
extern int label_count;

extern ForLoop loops[16];
extern int loop_count;

float get_num(char* name);
void set_num(char* name,float value);

int find_label(char* name);
void scan_labels();

#endif

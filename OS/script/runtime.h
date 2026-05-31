/*
* Script interpreter runtime.
*
* Defines the data structures used during the
* execution of programs, including:
*
* - Numeric variables.
* - Labels for execution jumps.
* - Control structures for FOR loops.
*
* Also declares functions for variable management
* and label lookup.
*/

/*
* Runtime do interpretador de scripts.
*
* Define as estruturas de dados utilizadas durante a
* execução dos programas, incluindo:
*
* - Variáveis numéricas.
* - Labels para saltos de execução.
* - Estruturas de controle de loops FOR.
*
* Também declara funções de gerenciamento de variáveis
* e busca de labels.
*/

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

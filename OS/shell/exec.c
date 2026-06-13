/*
* Script executor.
*
* Responsible for interpreting and executing the commands
* stored in the loaded program.
*
* Supported features:
* - Printing values (print)
* - Changing colors (color)
* - Labels and jumps (label/goto)
* - Drawing on the screen (plot)
* - Numeric variables
* - FOR/NEXT loops
* - Mathematical expression evaluation
*
* Execution can be interrupted by the ESC key.
*/

/*
* Executor de scripts.
*
* Responsável por interpretar e executar os comandos
* armazenados no programa carregado.
*
* Recursos suportados:
* - Impressão de valores (print)
* - Alteração de cores (color)
* - Labels e saltos (label/goto)
* - Desenho na tela (plot)
* - Variáveis numéricas
* - Loops FOR/NEXT
* - Avaliação de expressões matemáticas
*
* A execução pode ser interrompida pela tecla ESC.
*/


#include "../include/types.h"

#include "../drivers/vga.h"

#include "../lib/string.h"
#include "../lib/math.h"

#include "../kernel/panic.h"

#include "../script/runtime.h"

#include "parser.h"
#include "exec.h"
#include "shell.h"

#include "../lib/stdio.h"
#include "../include/globals.h"


extern void print_float(float f);

extern int stop_program;

extern void check_escape();

extern void set_num(char* name, float value);


/* ========================= */
/* EXECUTE */
/* ========================= */

void execute_program() {

    int i;

    print("\nRUNNING...\n");

    stop_program = 0;

    loop_count = 0;

    scan_labels();

    i = 0;

    while (i < prog_len) {

        char line[256];

        int li = 0;

        check_escape();

        if (stop_program) {

            print("\nSTOPPED\n");
            return;
        }

        while (
            i < prog_len &&
            program[i] != '\n'
        ) {

            if (li < 255)
                line[li++] = program[i];

            i++;
        }

        line[li] = 0;

        int cmd_start = 0;

        while (1) {

            char cmd[128];

            int ci = 0;

            while (
                line[cmd_start] == ' '
            ) {
                cmd_start++;
            }

            while (
                line[cmd_start] &&
                line[cmd_start] != ';'
            ) {

                if (ci < 127)
                    cmd[ci++] = line[cmd_start];

                cmd_start++;
            }

            cmd[ci] = 0;

            if (line[cmd_start] == ';')
                cmd_start++;

            /* ========================= */
            /* PRINT */
            /* ========================= */

            if (starts_with(cmd, "print ")) {

                char* expr = &cmd[6];

                float v = eval(expr);

                print_float(v);

                putc('\n');
            }

            /* ========================= */
            /* COLOR */
            /* ========================= */

            else if (starts_with(cmd, "color ")) {

                color =
                    (u8)eval(&cmd[6]);
            }

            /* ========================= */
            /* LABEL */
            /* ========================= */

            else if (starts_with(cmd, "label ")) {

            }

            /* ========================= */
            /* GOTO */
            /* ========================= */

            else if (starts_with(cmd, "goto ")) {

                int pos =
                    find_label(&cmd[5]);

                if (pos >= 0) {

                    i = pos;
                    break;
                }
            }

            /* ========================= */
            /* PLOT */
            /* ========================= */

            else if (starts_with(cmd, "plot ")) {

                char xs[32];
                char ys[32];

                int p = 5;

                int xi = 0;
                int yi = 0;

                while (
                    cmd[p] != ',' &&
                    cmd[p]
                ) {

                    if (xi < 31)
                        xs[xi++] = cmd[p];

                    p++;
                }

                xs[xi] = 0;

                if (cmd[p] == ',')
                    p++;

                while (cmd[p]) {

                    if (yi < 31)
                        ys[yi++] = cmd[p];

                    p++;
                }

                ys[yi] = 0;

                plot(
                    (int)eval(xs),
                    (int)eval(ys),
                    '*'
                );
            }

            /* ========================= */
            /* FOR */
            /* ========================= */

            else if (starts_with(cmd, "for ")) {

                char name[32];

                char start_s[32];
                char end_s[32];
                char step_s[32];

                int p = 4;

                int ni = 0;
                int si = 0;
                int ei = 0;
                int sti = 0;

                while (
                    cmd[p] != '=' &&
                    cmd[p]
                ) {

                    if (ni < 31)
                        name[ni++] = cmd[p];

                    p++;
                }

                name[ni] = 0;

                if (cmd[p] == '=')
                    p++;

                while (
                    cmd[p] != ' ' &&
                    cmd[p]
                ) {

                    if (si < 31)
                        start_s[si++] = cmd[p];

                    p++;
                }

                start_s[si] = 0;

                while (cmd[p] == ' ')
                    p++;

                if (
                    cmd[p] == 't' &&
                    cmd[p + 1] == 'o'
                ) {
                    p += 2;
                }

                while (cmd[p] == ' ')
                    p++;

                while (
                    cmd[p] != ' ' &&
                    cmd[p]
                ) {

                    if (ei < 31)
                        end_s[ei++] = cmd[p];

                    p++;
                }

                end_s[ei] = 0;

                while (cmd[p] == ' ')
                    p++;

                if (
                    cmd[p] == 's' &&
                    cmd[p + 1] == 't' &&
                    cmd[p + 2] == 'e' &&
                    cmd[p + 3] == 'p'
                ) {
                    p += 4;
                }

                while (cmd[p] == ' ')
                    p++;

                while (cmd[p]) {

                    if (sti < 31)
                        step_s[sti++] = cmd[p];

                    p++;
                }

                step_s[sti] = 0;

                if (loop_count < 16) {

                    strcpy(
                        loops[loop_count].var,
                        name
                    );

                    loops[loop_count].current =
                        eval(start_s);

                    loops[loop_count].end =
                        eval(end_s);

                    loops[loop_count].step =
                        eval(step_s);

                    loops[loop_count].pos = i;

                    set_num(
                        name,
                        loops[loop_count].current
                    );

                    loop_count++;
                }
            }

            /* ========================= */
            /* NEXT */
            /* ========================= */

            else if (starts_with(cmd, "next ")) {

                char* name = &cmd[5];

                int l;

                for (l = 0; l < loop_count; l++) {

                    if (
                        strcmp(
                            loops[l].var,
                            name
                        )
                    ) {

                        loops[l].current +=
                            loops[l].step;

                        set_num(
                            name,
                            loops[l].current
                        );

                        if (
                            loops[l].current <=
                            loops[l].end
                        ) {

                            i = loops[l].pos;
                        }

                        break;
                    }
                }
            }


            /* ========================= */
            /* ASSIGNMENT */
            /* ========================= */

            else {

                int eq = -1;
                int k;

                for (k = 0; cmd[k]; k++) {

                    if (cmd[k] == '=') {

                        eq = k;
                        break;
                    }
                }

                if (eq >= 0) {

                    char name[32];
                    char expr[64];

                    int ni = 0;
                    int ei = 0;

                    for (
                        k = 0;
                        k < eq;
                        k++
                    ) {

                        if (cmd[k] != ' ') {

                            if (ni < 31)
                                name[ni++] =
                                    cmd[k];
                        }
                    }

                    name[ni] = 0;

                    for (
                        k = eq + 1;
                        cmd[k];
                        k++
                    ) {

                        if (ei < 63)
                            expr[ei++] =
                                cmd[k];
                    }

                    expr[ei] = 0;

                    set_num(
                        name,
                        eval(expr)
                    );
                }
            }

            if (!line[cmd_start])
                break;
        }

        if (
            i < prog_len &&
            program[i] == '\n'
        ) {

            i++;
        }
    }

    print("\nDONE\n");
}

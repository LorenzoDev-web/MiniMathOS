/*
* Management of interpreter labels.
*
* Scans the source code for "label" commands
* and stores their names and positions to allow
* execution jumps (goto/jump) during script execution.
*
* Functions:
* - scan_labels(): finds and registers all labels.
* - find_label(): searches for the position of a label by name.
*/

/*
* Gerenciamento de labels (rótulos) do interpretador.
*
* Realiza a varredura do código-fonte em busca de comandos
* "label" e armazena seus nomes e posições para permitir
* saltos de execução (goto/jump) durante a execução do script.
*
* Funções:
* - scan_labels() : encontra e registra todos os labels.
* - find_label() : procura a posição de um label pelo nome.
*/

#include "../include/types.h"

#include "../lib/string.h"

#include "../script/runtime.h"

#include "../shell/shell.h"
#include "../include/globals.h"


/* ========================= */
/* LABELS */
/* ========================= */

void scan_labels() {

    int i = 0;

    label_count = 0;

    while (i < prog_len) {

        if (starts_with(&program[i], "label ")) {

            int start;
            int len;
            int j;

            i += 6;

            start = i;

            while (

                i < prog_len &&
                program[i] != '\n'

            ) {
                i++;
            }

            len = i - start;

            if (label_count < 32) {

                for (j = 0; j < len && j < 31; j++) {

                    labels[label_count].name[j] =
                        program[start + j];
                }

                labels[label_count].name[j] = 0;

                labels[label_count].pos = i;

                label_count++;
            }
        }

        while (

            i < prog_len &&
            program[i] != '\n'

        ) {
            i++;
        }

        i++;
    }
}

int find_label(char* name) {

    int i;

    for (i = 0; i < label_count; i++) {

        if (strcmp(labels[i].name, name))
            return labels[i].pos;
    }

    return -1;
}

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

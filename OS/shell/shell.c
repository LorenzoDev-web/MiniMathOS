#include "../include/globals.h"
#include "../drivers/vga.h"
#include "../lib/string.h"
#include "../shell/shell.h"
#include "../shell/exec.h"

void shell() {

    input[input_len] = 0;

    if (strcmp(input, "clear")) {

        clear();
    }

    else if (strcmp(input, "edit")) {

        editing = 1;

        prog_len = 0;

        print("\nEDITOR MODE\n");
        print("ESC = exit\n\n");
    }

    else if (strcmp(input, "run")) {

        execute_program();
    }

    else if(strcmp(input, "help")) {

        print("\nCommands:\n");
        print("help\n");
        print("about\n");
        print("mem\n");
        print("clear\n");
        print("edit\n");
        print("run\n");
    }

    else if(strcmp(input, "about")) {
        print("\nMini Math OS");
        print("\nVersion: 0.01");
        print("\nDeveloper Credits: Instagram: lore_nzoegidio; Github: LorenzoDevWeb");
    }

    else if(strcmp(input, "mem")) {

        print("\nMemory stats\n");

        print("Variables: ");
        print_int(num_var_count);
        putc('\n');

        print("Labels: ");
        print_int(label_count);
        putc('\n');

        print("Loops: ");
        print_int(loop_count);
        putc('\n');

        print("Program bytes: ");
        print_int(prog_len);
        putc('\n');
    }

    else {

        print("\nUnknown command\n");
    }

    input_len = 0;

    print("\n> ");
}

/*
* System shell.
*
* Responsible for processing commands typed by the
* user and executing the available OS functionalities.
*
* Supported commands:
* - help : displays the list of commands.
* - about : shows system information.
* - mem : displays memory and runtime statistics.
* - clear : clears the screen.
* - edit : enters script editor mode.
* - run : executes the loaded program.
*/

/*
* Shell do sistema.
*
* Responsável por processar os comandos digitados pelo
* usuário e executar as funcionalidades disponíveis do OS.
*
* Comandos suportados:
* - help : exibe a lista de comandos.
* - about : mostra informações do sistema.
* - mem : exibe estatísticas de memória e runtime.
* - clear : limpa a tela.
* - edit : entra no modo editor de scripts.
* - run : executa o programa carregado.
*/

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

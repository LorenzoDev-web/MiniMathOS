/*
* Management of numerical variables of the interpreter.
*
* Maintains a table of variables identified by name,
* allowing to store and retrieve float type values
* during script execution.
*
* Functions:
* - set_num() : creates or updates a variable.
* - get_num() : gets the value of a variable.
*/

/*
* Gerenciamento de variáveis numéricas do interpretador.
*
* Mantém uma tabela de variáveis identificadas por nome,
* permitindo armazenar e recuperar valores do tipo float
* durante a execução dos scripts.
*
* Funções:
* - set_num() : cria ou atualiza uma variável.
* - get_num() : obtém o valor de uma variável.
*/

extern int strcmp(char* a, char* b);
extern void strcpy(char* dst, char* src);

typedef struct {

    char name[32];
    float value;

} NumVar;

NumVar num_vars[64];

int num_var_count = 0;

void set_num(char* name, float value) {

    int i;

    for (i = 0; i < num_var_count; i++) {

        if (strcmp(num_vars[i].name, name)) {

            num_vars[i].value = value;
            return;
        }
    }

    if (num_var_count >= 64)
        return;

    strcpy(num_vars[num_var_count].name, name);

    num_vars[num_var_count].value = value;

    num_var_count++;
}

float get_num(char* name) {

    int i;

    for (i = 0; i < num_var_count; i++) {

        if (strcmp(num_vars[i].name, name))
            return num_vars[i].value;
    }

    return 0;
}

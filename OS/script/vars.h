// vars.c Header

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

/* ========================= */
/* STRING */
/* ========================= */

// String manipulation
// Manipulação de strings

int strcmp(char* a, char* b) {

    while (*a && *b) {

        if (*a != *b)
            return 0;

        a++;
        b++;
    }

    return (*a == 0 && *b == 0);
}

void strcpy(char* dst, char* src) {

    while (*src)
        *dst++ = *src++;

    *dst = 0;
}

int starts_with(char* str, char* prefix) {

    while (*prefix) {

        if (*str != *prefix)
            return 0;

        str++;
        prefix++;
    }

    return 1;
}

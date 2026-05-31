#include "../lib/math.h"
#include "../kernel/panic.h"
#include "../script/runtime.h"
#include "../lib/string.h"

extern float get_num(char* name);
extern void set_num(char* name, float value);


/* ========================= */
/* EXPRESSION PARSER */
/* ========================= */

char* expr_ptr;

void skip_spaces() {

    while (*expr_ptr == ' ')
        expr_ptr++;
}

float parse_expr();

float parse_number() {

    char buf[32];

    int i = 0;

    if (*expr_ptr == '-') {

        buf[i++] = *expr_ptr++;
    }

    while (

        ((*expr_ptr >= '0') &&
         (*expr_ptr <= '9'))

        ||

        (*expr_ptr == '.')

    ) {

        if (i < 31)
            buf[i++] = *expr_ptr;

        expr_ptr++;
    }

    buf[i] = 0;

    return atof_simple(buf);
}

float parse_factor() {

    skip_spaces();

    /* PARENTHESIS */

    if (*expr_ptr == '(') {

        expr_ptr++;

        float v = parse_expr();

        skip_spaces();

        if (*expr_ptr == ')')
            expr_ptr++;

        return v;
    }

    /* SIN */

    if (

        expr_ptr[0] == 's' &&
        expr_ptr[1] == 'i' &&
        expr_ptr[2] == 'n'

    ) {

        expr_ptr += 3;

        skip_spaces();

        if (*expr_ptr == '(')
            expr_ptr++;

        float v = parse_expr();

        skip_spaces();

        if (*expr_ptr == ')')
            expr_ptr++;

        return sin(v);
    }

    // COS

    if (
        expr_ptr[0] == 'c' &&
        expr_ptr[1] == 'o' &&
        expr_ptr[2] == 's'
    ) {
        expr_ptr += 3;

        skip_spaces();
        
        if(*expr_ptr == '(') 
            expr_ptr++;

        float v = parse_expr();
        skip_spaces();
        
        if(*expr_ptr == ')')
            expr_ptr++;

        return cos(v);
    }

    // tan
    if (
        expr_ptr[0] == 't' &&
        expr_ptr[1] == 'a' &&
        expr_ptr[2] == 'n'
    ) {
        expr_ptr += 3;
        skip_spaces();

        if(*expr_ptr == '(')
            expr_ptr++;

        float v = parse_expr();
        skip_spaces();

        if(*expr_ptr == ')')
            expr_ptr++;

        return tan(v);
    }

    // SQRT
    if (

        expr_ptr[0] == 's' &&
        expr_ptr[1] == 'q' &&
        expr_ptr[2] == 'r' &&
        expr_ptr[3] == 't'

    ) {

        expr_ptr += 4;

        skip_spaces();

        if (*expr_ptr == '(')
            expr_ptr++;

        float v = parse_expr();

        skip_spaces();

        if (*expr_ptr == ')')
            expr_ptr++;

        return sqrt(v);
    }

    /* POW */

    if (

        expr_ptr[0] == 'p' &&
        expr_ptr[1] == 'o' &&
        expr_ptr[2] == 'w'

    ) {

        expr_ptr += 3;

        skip_spaces();

        if (*expr_ptr == '(')
            expr_ptr++;

        float a = parse_expr();

        skip_spaces();

        if (*expr_ptr == ',')
            expr_ptr++;

        float b = parse_expr();

        skip_spaces();

        if (*expr_ptr == ')')
            expr_ptr++;

        return powi(a, (int)b);
    }

    /* LN */

    if (

        expr_ptr[0] == 'l' &&
        expr_ptr[1] == 'n'

    ) {

        expr_ptr += 2;

        skip_spaces();

        if (*expr_ptr == '(')
            expr_ptr++;

        float v = parse_expr();

        skip_spaces();

        if (*expr_ptr == ')')
            expr_ptr++;

        return ln(v);
    }

    // ABS
    if (
        expr_ptr[0] == 'a' &&
        expr_ptr[1] == 'b' &&
        expr_ptr[2] == 's'
    ) {
        expr_ptr += 3;
        skip_spaces();

        if(*expr_ptr == '(')
            expr_ptr++;

        float v = parse_expr();
        skip_spaces();

        if(*expr_ptr == ')')
            expr_ptr++;

        return fabs_simple(v);
    }

 
    /* VARIABLE */

    if (

        (*expr_ptr >= 'a' &&
         *expr_ptr <= 'z')

    ) {

        char name[32];

        int i = 0;

        while (

            (*expr_ptr >= 'a' &&
             *expr_ptr <= 'z')

        ) {

            if (i < 31)
                name[i++] = *expr_ptr;

            expr_ptr++;
        }

        name[i] = 0;

        return get_num(name);
    }

    /* NUMBER */

    return parse_number();
}

float parse_term() {

    float v = parse_factor();

    while (1) {

        skip_spaces();

        if (*expr_ptr == '*') {

            expr_ptr++;

            v *= parse_factor();
        }

        else if (*expr_ptr == '/') {

            expr_ptr++;

            float d = parse_factor();

            if (
                d > -0.00001f &&
                d <  0.00001f
            ) {

                panic("DE: DIVIDE ERROR");
            }

            v /= d;
        }

        else {

            break;
        }

        skip_spaces();
    }

    return v;
}


float parse_expr() {

    float v = parse_term();

    while (1) {

        skip_spaces();

        if (*expr_ptr == '+') {

            expr_ptr++;

            v += parse_term();
        }

        else if (*expr_ptr == '-') {

            expr_ptr++;

            v -= parse_term();
        }

        else
            break;
    }

    return v;
}

float eval(char* s) {

    expr_ptr = s;

    return parse_expr();
}

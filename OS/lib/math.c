/*
* Basic mathematical library of the kernel.
*
* Implements essential mathematical functions without depending
* on the system's standard library, allowing their use in
* bare-metal environments and during the initial phases of the kernel.
*
* Available functions:
* - sin(), cos(), tan()
* - sqrt()
* - powi()
* - ln(), log10()
* - fabs_simple()
* - atof_simple()
*
* Some functions use numerical approximations and mathematical series
* to reduce external dependencies.
*/

/*
* Biblioteca matemática básica do kernel.
*
* Implementa funções matemáticas essenciais sem depender
* da biblioteca padrão do sistema, permitindo seu uso em
* ambientes bare-metal e durante as fases iniciais do kernel.
*
* Funções disponíveis:
* - sin(), cos(), tan()
* - sqrt()
* - powi()
* - ln(), log10()
* - fabs_simple()
* - atof_simple()
*
* Algumas funções utilizam aproximações numéricas e séries
* matemáticas para reduzir dependências externas.
*/


/* ========================= */
/* MATH */
/* ========================= */

float sin(float x) {

    while (x > 3.14159265f)
        x -= 6.28318530f;

    while (x < -3.14159265f)
        x += 6.28318530f;

    float x2 = x * x;

    return
        x
        - (x2 * x) / 6.0f
        + (x2 * x2 * x) / 120.0f
        - (x2 * x2 * x2 * x) / 5040.0f
        + (x2 * x2 * x2 * x2 * x) / 362880.0f;
}

float cos(float x) {

    while (x > 3.14159265f)
        x -= 6.28318530f;

    while (x < -3.14159265f)
        x += 6.28318530f;

    float x2 = x * x;

    return
        1.0f
        - x2 / 2.0f
        + (x2 * x2) / 24.0f
        - (x2 * x2 * x2) / 720.0f
        + (x2 * x2 * x2 * x2) / 40320.0f;
}

float tan(float x) {
    return sin(x) / cos(x);
}

float sqrt(float x) {

    if (x <= 0.0f)
        return 0.0f;

    float r = x;

    int i;

    for (i = 0; i < 16; i++) {

        if (r == 0.0f)
            break;

        r = 0.5f * (r + x / r);
    }

    return r;
}

float powi(float base, int exp) {

    float r = 1.0f;

    int i;

    if (exp < 0) {

        exp = -exp;

        for (i = 0; i < exp; i++)
            r *= base;

        return 1.0f / r;
    }

    for (i = 0; i < exp; i++)
        r *= base;

    return r;
}

float ln(float x) {

    if (x <= 0.0f)
        return 0.0f;

    float y = (x - 1.0f) / (x + 1.0f);

    float y2 = y * y;

    float result = 0.0f;

    float term = y;

    int n;

    for (n = 1; n < 20; n += 2) {

        result += term / n;

        term *= y2;
    }

    while (x > 2.0f) {
        x *= 0.5f;
        result += 0.69314718f;
    }

    return 2.0f * result;
}

float log10(float x) {

    return ln(x) / 2.30258509f;
}

float fabs_simple(float x) {

    if (x < 0.0f)
        return -x;

    return x;
}

float atof_simple(char* s) {

    float result = 0;
    float frac = 0;
    float div = 1;

    int after_dot = 0;
    int negative = 0;

    if (*s == '-') {

        negative = 1;
        s++;
    }

    while (*s) {

        if (*s == '.') {

            after_dot = 1;
        }

        else if (*s >= '0' && *s <= '9') {

            if (!after_dot) {

                result =
                    result * 10 +
                    (*s - '0');
            }

            else {

                frac =
                    frac * 10 +
                    (*s - '0');

                div *= 10;
            }
        }

        s++;
    }

    result = result + frac / div;

    if (negative)
        result = -result;

    return result;
}



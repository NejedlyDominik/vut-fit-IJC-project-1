/**
 * error.c
 * Reseni IJC-DU1, priklad b), 20.3. 2019
 * Autor: Dominik Nejedly, FIT
 * Prelozeno: gcc 7.4.0
 * Modul s definicemi chybovych funkci.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

/**
 * Funkce tiskne chybove hlaseni v danem formatu.
 */
void warning_msg(const char *fmt, ...)
{
    va_list arguments;

    fprintf(stderr, "CHYBA: ");
    va_start(arguments, fmt);
    vfprintf(stderr, fmt, arguments);
    va_end(arguments);
}

/**
 * Funkce tiskne chybove hlaseni v danem formatu a ukonci program.
 */
void error_exit(const char *fmt, ...)
{
    va_list arguments;

    fprintf(stderr, "CHYBA: ");
    va_start(arguments, fmt);
    vfprintf(stderr, fmt, arguments);
    va_end(arguments);

    exit(1);
}

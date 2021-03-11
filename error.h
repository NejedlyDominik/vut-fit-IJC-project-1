/**
 * error.h
 * Resení IJC-DU1, priklad b), 20.3. 2019
 * Autor: Dominik Nejedly, FIT
 * Prelozeno: gcc 7.4.0
 * Hlavickovy soubor obsahujici prototypy chybovych funkci.
 */

#ifndef ERROR_H_INCLUDED
#define ERROR_H_INCLUDED

void warning_msg(const char *fmt, ...);
void error_exit(const char *fmt, ...);

#endif


/**
 * ppm.h
 * Reseni IJC-DU1, priklad b), 20.3. 2019
 * Autor: Dominik Nejedly, FIT
 * Prelozeno: gcc 7.4.0
 * Hlavickovy soubor obsahujici prototypy funkci pro praci s ppm souborem.
 */

#ifndef PPM_H_INCLUDED
#define PPM_H_INCLUDED

/**
 * Struktura nesouci informace o ppm obrazku.
 */
struct ppm
{
unsigned xsize;     // velikost v ose x
unsigned ysize;     // velikost v ose y
char data[];        // samotna data
};

struct ppm * ppm_read(const char * filename);
void ppm_free(struct ppm *p);

#endif

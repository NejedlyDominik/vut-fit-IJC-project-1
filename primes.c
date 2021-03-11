/**
 * primes.c
 * Reseni IJC-DU1, priklad a), 20.3. 2019
 * Autor: Dominik Nejedly, FIT
 * Prelozeno: gcc 7.4.0
 * Modul hlavniho programu.
 */

#include <stdio.h>
#include <stdlib.h>
#include "bit_array.h"
#include "eratosthenes.h"

#define NUMBER 10   // pocet hledanych nejvetsich prvocisel

/**
 * Zavola makro/funkci pro vytvoreni bitoveho pole dane velikosti, nad kterym provede funkci Eratosthenes a najde prvocisla.
 * Poslednich deset nalezenych prvocisel vytiskne vzestupne na standardni vystup.
 */
int main()
{
    // vytvori bitove pole
    bit_array_create(bit_field, 123000000);

    Eratosthenes(bit_field);

    // pomocne pole pro ulozeni 10 nejvetsich prvocisel
    unsigned long prime_array[NUMBER];

    // aktualni pocet nejvetsich nalezenych prvocisel
    int counter = 0;

    // prochazeni bitoveho pole od konce a ukladani nalezenych prvocisel do pomocneho pole
    for(unsigned long i = (bit_array_size(bit_field) - 1); i > 1 && counter < NUMBER; i--)
    {
        if(!(bit_array_getbit(bit_field, i)))
        {
            prime_array[counter] = i;

            counter++;
        }
    }

    // tisk pomocneho pole na standardni vystup od konce
    for(counter = NUMBER - counter + 1; counter <= NUMBER; counter++)
    {
        printf("%lu\n", prime_array[NUMBER - counter]);
    }
    return 0;
}

/**
 * eratosthenes.c
 * Reseni IJC-DU1, priklad a), 20.3. 2019
 * Autor: Dominik Nejedlý, FIT
 * Prelozeno: gcc 7.4.0
 * Modul s funkci Eratosthnenes, ktera implementuje algoritmus Eratosthenovo sito.
 * Slouzi pro vyhledavani prvocisel.
 */

#include <stdio.h>
#include <math.h>
#include "bit_array.h"

/**
 * Funkce prochazi vynulovane bitove pole. Na prvociselnych indexech nechava bit s hodnotou 0 a na ostatnich nastavuje 1.
 * Na pocatku automaticky nastavuje bity na indexech 0 a 1 na 1 a pote vzdy, kdyz narazi na bit s hodnotou 0 jedna se o prvocislo,
 * pricemz bity na indexech odpovidajicich nasobkum daneho prvocisla nastavi na 1. Takhle postupuje po jednotlivych bitech,
 * dokud neprekroci hranici odmocniny z celkoveho poctu bitu v poli.
 */
void Eratosthenes(bit_array_t pole)
{
    // nastaveni bitu na indexu 0 a 1 na 1
    if(bit_array_size(pole) > 0)
    {
        bit_array_setbit(pole, 0, 1);
    }

    if(bit_array_size(pole) > 1)
    {
        bit_array_setbit(pole, 1, 1);
    }

    // Pro zvyseni efektivity se nastavi nasobky 2 na 1 jeste pred samotnym algoritmem.
    for(unsigned long i = 4; i < bit_array_size(pole); i += 2)
    {
        bit_array_setbit(pole, i, 1);
    }

    // Nasobky 2 jsou nastaveny, je tedy mozne zacit od 3 a jit pouze po lichych cislech.
    for(unsigned long i = 3; i < sqrt(bit_array_size(pole)); i += 2)
    {
        if(!(bit_array_getbit(pole, i)))
        {
            for(unsigned long j = i * i; j < bit_array_size(pole); j += i * 2)
            {
                bit_array_setbit(pole, j, 1);
            }
        }
    }
}

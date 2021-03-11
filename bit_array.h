/**
 * bit_array.h
 * Reseni IJC-DU1, priklad a), 20.3. 2019
 * Autor: Dominik Nejedly, FIT
 * Prelozeno: gcc 7.4.0
 * Hlavickovy soubor obsahujici definice maker a inline funkci.
 */

#ifndef BIT_ARRAY_H_INCLUDED
#define BIT_ARRAY_H_INCLUDED

#include <assert.h>
#include <stdlib.h>
#include <limits.h>
#include "error.h"

typedef unsigned long *bit_array_t;     // datovy typ - ukazatel na unsigned long

#define BYTE_UL_SIZE sizeof(unsigned long)          // velikost unsigned long v bajtech
#define BIT_UL_SIZE (sizeof(unsigned long) << 3)    // velikost unsigned long v bitech

/**
 * Vytvori pole dane velikosti v bitech. Na nultem indexu ulozi jeho velikost a cele pole vynuluje.
 */
#define bit_array_create(jmeno_pole, velikost) \
    static_assert(velikost > 0 && velikost <= ULONG_MAX, "Nepodporovana velikost pole."); \
    unsigned long jmeno_pole[((velikost)/BIT_UL_SIZE) + (((velikost) % BIT_UL_SIZE) ? 2 : 1)] = {(velikost)}

/**
 * Ekvivalent predchoziho makra. Dynamicky alokuje pamet pro pole dane velikosti v bitech.
 * Cele pole nuluje a na nultem indexu ulozi jeho velikost.
 * Pokud alokace selze, ukonci program.
 */
#define bit_array_alloc(jmeno_pole, velikost) \
    assert(velikost > 0 && velikost <= ULONG_MAX); \
    bit_array_t jmeno_pole = calloc((((velikost)/BIT_UL_SIZE) + (((velikost) % BIT_UL_SIZE) ? 2 : 1)), BYTE_UL_SIZE); \
    ((jmeno_pole == NULL) ? (error_exit("bit_array_alloc: Chyba alokace pameti\n"), 0) : (jmeno_pole[0] = (velikost), 1))

#ifndef USE_INLINE  //pokud je definovano USE_INLINE pouziji se misto maker inline funkce

/**
 * Uvolni pamet dynamicky alokovaneho pole.
 */
#define bit_array_free(jmeno_pole) free(jmeno_pole)

/**
 * Vrati deklarovanou velikost pole v bitech (ulozenou v poli)
 */
#define bit_array_size(jmeno_pole) jmeno_pole[0]

/**
 * Nastavi zadany bit v poli na hodnotu zadanou vyrazem (nulovy vyraz == bit 0, nenulovy vyraz == bit 1).
 * Pokud je zadany index mimo rozsah pole, vytiskne chybove hlaseni a ukonci program.
 */
#define bit_array_setbit(jmeno_pole, index, vyraz) \
\
    (((index) < bit_array_size(jmeno_pole)) ? \
    \
        ((vyraz) ? \
        \
            (jmeno_pole[(index)/BIT_UL_SIZE + 1] |= 1L << ((index) % BIT_UL_SIZE)) \
            : \
            (jmeno_pole[(index)/BIT_UL_SIZE + 1] &= ~(1L << ((index) % BIT_UL_SIZE)))) \
        : \
        (error_exit("bit_array_setbit: Index %lu mimo rozsah 0..%lu\n", index, bit_array_size(jmeno_pole)), 0))

/**
 * Ziska hodnotu zadaneho bitu, vraci hodnotu 0 nebo 1.
 */
#define bit_array_getbit(jmeno_pole, index) \
\
    (((index) < bit_array_size(jmeno_pole)) ? \
    \
        ((jmeno_pole[(index)/BIT_UL_SIZE + 1] & (1L << ((index) % BIT_UL_SIZE))) ? 1 : 0) \
        : \
        (error_exit("bit_array_getbit: Index %lu mimo rozsah 0..%lu\n", index, bit_array_size(jmeno_pole)), 0))

#else

/**
 * Ekvivalent makra bit_array_free.
 * Uvolni pamet dynamicky alokovaneho pole.
 */
inline void bit_array_free(bit_array_t jmeno_pole)
{
    free(jmeno_pole);
}

/**
 * Ekvivalent makra bit_array_size.
 * Vrati deklarovanou velikost pole v bitech (ulozenou v poli)
 */
inline unsigned long bit_array_size(bit_array_t jmeno_pole)
{
    return jmeno_pole[0];
}

/**
 * Ekvivalent makra bit_array_setbit.
 * Nastavi zadany bit v poli na hodnotu zadanou vyrazem (nulový vyraz == bit 0, nenulovy vyraz == bit 1).
 * Pokud je zadany index mimo rozsah pole, vytiskne chybove hlaseni a ukonci program.
 */
inline void bit_array_setbit(bit_array_t jmeno_pole, unsigned long index, int vyraz)
{
    if(index >= bit_array_size(jmeno_pole))
    {
        error_exit("bit_array_setbit: Index %lu mimo rozsah 0..%lu\n", index, bit_array_size(jmeno_pole));
    }

    if(vyraz)
    {
        jmeno_pole[index/BIT_UL_SIZE + 1] |= 1L << (index % BIT_UL_SIZE);
    }
    else
    {
        jmeno_pole[index/BIT_UL_SIZE + 1] &= ~(1L << (index % BIT_UL_SIZE));
    }
}

/**
 * Ekvivalent makra bit_array_getbit.
 * Ziska hodnotu zadaneho bitu, vraci hodnotu 0 nebo 1.
 */
inline int bit_array_getbit(bit_array_t jmeno_pole, unsigned long index)
{
    if(index >= bit_array_size(jmeno_pole))
    {
        error_exit("bit_array_getbit: Index %lu mimo rozsah 0..%lu\n", index, bit_array_size(jmeno_pole));
    }

    return (jmeno_pole[index/BIT_UL_SIZE + 1] & (1L << (index % BIT_UL_SIZE))) ? 1 : 0;
}

#endif

#endif

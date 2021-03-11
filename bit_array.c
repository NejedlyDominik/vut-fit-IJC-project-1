/**
 * bit_array.c
 * Reseni IJC-DU1, priklad a), 20.3. 2019
 * Autor: Dominik Nejedly, FIT
 * Prelozeno: gcc 7.4.0
 * Modul s externimi definicemi inline funkci.
 */

#include "bit_array.h"

#ifdef USE_INLINE

extern inline void bit_array_free(bit_array_t jmeno_pole);
extern inline unsigned long bit_array_size(bit_array_t jmeno_pole);
extern inline void bit_array_setbit(bit_array_t jmeno_pole, unsigned long index, int vyraz);
extern inline int bit_array_getbit(bit_array_t jmeno_pole, unsigned long index);

#endif

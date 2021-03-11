/**
 * steg-decode.c
 * Reseni IJC-DU1, priklad b), 20.3. 2019
 * Autor: Dominik Nejedly, FIT
 * Prelozeno: gcc 7.4.0
 * Modul hlavniho programu.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "ppm.h"
#include "bit_array.h"
#include "eratosthenes.h"

#define RGB 3               // pocet barevnych slozek obrazku
#define CHAR_BIT_SIZE 8     // velikost datoveho typu char v bitech
#define INITIAL_PRIME 19    // pocatecni prvocislo pro dekodovani
#define INITIAL_SIZE 50     // pocatecni velikost pole pro ukladani dekodovane zpravy
#define SIZE_EXTENSION 25   // Velikost, o kterou se pole postupne zvetsuje.

/**
 * Provede dekodovani zpravy ze souboru ppm ulozenou po jednotlivych bitech na nejnizsich bitech
 * vybranych bajtu jednotlivych barevnych slozek v datech obrazku.
 */
int main(int argc, char *argv[])
{
    // kontrola poctu argumentu
    if(argc != 2)
    {
        fprintf(stderr, "Nepodporovany pocet argumentu.\n");
        return 1;
    }

    // vytvoreni struktury a nacteni dat souboru
    struct ppm *ppm_pointer = ppm_read(argv[1]);

    // kontrola alokace pameti pro strukturu
    if(ppm_pointer == NULL)
    {
        error_exit("Nacitani souboru %s selhalo.\n", argv[1]);
    }

    char symbol = 0;    // promenna pro ukladani jednotlivych dekodovanych znaku
    int counter = 0;
    bool EOS = false;   // pro kontrolu znaku konce retezce

    // alokace pameti pro bitove pole
    bit_array_alloc(bit_field, RGB * ppm_pointer -> xsize * ppm_pointer -> ysize);

    char *decoded_msg = malloc(INITIAL_SIZE);   // pole pro ulozeni dekodovane zpravy
    char *new_decoded_msg;                      // pomocna promenna

    // kontrola alokace
    if(decoded_msg == NULL)
    {
        bit_array_free(bit_field);
        ppm_free(ppm_pointer);
        fprintf(stderr, "Chyba pri alokaci pameti pro dekodovanou zpravu.\n");
        return 2;
    }

    int current_size = INITIAL_SIZE;    // aktualni velikost pole pro ulozeni dekodovane zpravy
    int current_index = 0;              // aktualni index v poli pro ulozeni dekodovane zpravy

    Eratosthenes(bit_field);

    // prochazeni prvocisel a sbirani hodnot pro dekodovani zpravy
    for(unsigned int i = INITIAL_PRIME; i < bit_array_size(bit_field); i++)
    {
        // naplneni promenne symbol znakem
        if(!bit_array_getbit(bit_field, i))
        {
            symbol |= ((ppm_pointer -> data[i] & 1) << counter);
            counter++;

            // Pokud je promenna symbol naplnena, ulozi ji do pole pro dekodovanou zpravu.
            if(counter == CHAR_BIT_SIZE)
            {
                // Pokud je aktualni index roven velikosti pole pro dekodovanou zpravu, rozsiri se pole.
                if(current_index == current_size)
                {
                    // Pokud selze dealokace, program skonci s chybou.
                    if((new_decoded_msg = realloc(decoded_msg, current_size + SIZE_EXTENSION)) == NULL)
                    {
                        free(decoded_msg);
                        bit_array_free(bit_field);
                        ppm_free(ppm_pointer);
                        fprintf(stderr, "Chyba pri realokaci pameti pro dekodovanou zpravu.");
                        return 3;
                    }

                    decoded_msg = new_decoded_msg;

                    current_size += SIZE_EXTENSION; // zvetseni aktualni velikosti
                }
                decoded_msg[current_index] = symbol;

                // Pokud je symbol roven znaku konce retezce dekodovani konci.
                if(symbol == '\0')
                {
                    EOS = true;
                    break;
                }

                counter = 0;        // reset promennych pro dalsi symbol
                symbol = 0;
                current_index++;    // posun indexu
            }
        }
    }

    // uvolneni alokovane pameti
    bit_array_free(bit_field);
    ppm_free(ppm_pointer);

    // Pokud retezec neobsahuje znak konce retezce, program konci s chybou.
    if(EOS == false)
    {
        free(decoded_msg);
        error_exit("Zprava neni ukoncena znakem '\\0'.\n");
    }

    // tisk dekodovane zpravy
    printf("%s\n", decoded_msg);

    free(decoded_msg);

    return 0;
}

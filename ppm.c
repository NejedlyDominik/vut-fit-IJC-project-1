/**
 * ppm.c
 * Reseni IJC-DU1, priklad b), 20.3. 2019
 * Autor: Dominik Nejedly, FIT
 * Prelozeno: gcc 7.4.0
 * Modul obsahujici definice funkce pro praci s ppm souborem.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "error.h"
#include "ppm.h"

/**
 * Funkce zkontroluje format ppm souboru a nahraje ho do pro nej urcene struktury.
 */
struct ppm * ppm_read(const char * filename)
{
    FILE *file;
    file = fopen(filename, "rb");

    // kontrola otevreni souboru
    if(file == NULL)
    {
        warning_msg("Soubor %s se nepodarilo otevrit.\n", filename);
        return NULL;
    }

    int x;              // hodnota osy x
    int y;              // hodnota osy y
    int RGB_ceiling;    // maximalni hodnota barvove slozky

    // kontrola formatu souboru a nacteni zakladnich dat
    if(fscanf(file, "P6 %d %d %d ", &x, &y, &RGB_ceiling) != 3)
    {
        warning_msg("Chybny format souboru %s.\n", filename);
        fclose(file);
        return NULL;
    }

    // kontrola rozsahu obrazku
    if(x <= 0 || y <= 0 || x > 8000 || y > 8000)
    {
        warning_msg("Nepodporovane rozmery obrazku %s.\n", filename);
        fclose(file);
        return NULL;
    }

    // kontrola maximalni barvove slozky
    if(RGB_ceiling != 255)
    {
        warning_msg("Nepodporovana velikost barvove slozky obrazku %s.\n", filename);
        fclose(file);
        return NULL;
    }

    // alokace pameti struktury pro data souboru
    struct ppm *ppm_image_p = malloc(sizeof(struct ppm) + (3 * x * y));

    // kontrola alokace
    if(ppm_image_p == NULL)
    {
        warning_msg("Alokace pameti struktury se nezdarila.\n");
        fclose(file);
        return NULL;
    }

    // predani souradnic do struktury
    ppm_image_p -> xsize = x;
    ppm_image_p -> ysize = y;

    // nacteni obsahu souboru do dat struktury
    if(fread(ppm_image_p -> data, 1, (3 * x * y), file) != (unsigned int)(3 * x * y))
    {
        warning_msg("Nacitani dat obrazku %s selhalo.\n", filename);
        ppm_free(ppm_image_p);
        fclose(file);
        return NULL;
    }

    fclose(file);
    return ppm_image_p;
}

/**
 * Funkce uvolni pamet alokovanou pro strukturu.
 */
void ppm_free(struct ppm *p)
{
    free(p);
}

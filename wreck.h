#ifndef WRECK_H
#define WRECK_H 1

/** 
 * Read and process data on shipwrecks in Italy as described in [Mappa dei relitti in Italia](http://www.datiopen.it/en/opendata/Mappa_dei_relitti_in_Italia)
*/

#include <stdint.h>
#include <stdlib.h>
#include <time.h>

#define WRCK_STR_SIZE 50
#define WRCK_CSV_SEP ';'

typedef struct
{
    char comune[WRCK_STR_SIZE];
    char provincia[WRCK_STR_SIZE];
    char regione[WRCK_STR_SIZE];
    char nome[WRCK_STR_SIZE];
    uint_least64_t osm_id; // OSM moved to 64 bits <https://wiki.openstreetmap.org/wiki/64-bit_Identifiers>
    time_t ins_date;
    double longitudine;
    double latitudine;
} WreckData;


// Prototypes

int csv_row_to_wreck(char *line, WreckData *wreck);
void show_wreck(WreckData *wreck);

#endif
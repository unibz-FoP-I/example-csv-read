#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "wreck.h"

static char *get_next_token(char* current, char sep) {
    char *next = strchr(current, sep);
    if (next) {
        next[0] = 0;
        return next + 1;
    }
    return 0;
}

int csv_row_to_wreck(char *line, WreckData *wreck) {
    if (wreck)
    {
        memset(wreck, 0, sizeof(*wreck));
        char *token = line;
        char *next_token = get_next_token(line, WRCK_CSV_SEP);
        // Comune
        if (!token) return 0;
        strncpy(wreck->comune, token, WRCK_STR_SIZE - 1);
        token = next_token;
        next_token = get_next_token(token, WRCK_CSV_SEP);

        // Provincia
        if (!token) return 0;
        strncpy(wreck->provincia, token, WRCK_STR_SIZE - 1);
        token = next_token;
        next_token = get_next_token(token, WRCK_CSV_SEP);

        // Regione
        if (!token) return 0;
        strncpy(wreck->regione, token, WRCK_STR_SIZE - 1);
        token = next_token;
        next_token = get_next_token(token, WRCK_CSV_SEP);

        // Nome
        if (!token) return 0;
        strncpy(wreck->nome, token, WRCK_STR_SIZE - 1);
        token = next_token;
        next_token = get_next_token(token, WRCK_CSV_SEP);

        // Anno inserimento (skip)
        if (!token) return 0;
        token = next_token;
        next_token = get_next_token(token, WRCK_CSV_SEP);

        // Data e ora inserimento
        if (!token) return 0;
        struct tm tm;
        if (!strptime(token, "%FT%TZ", &tm)) return 0;
        wreck->ins_date = mktime(&tm);
        token = next_token;
        next_token = get_next_token(token, WRCK_CSV_SEP);

        // Identificatore in OpenStreetMap
        if (!token) return 0;
        if (!(wreck->osm_id = strtoll(token, NULL, 10))) return 0;
        token = next_token;
        next_token = get_next_token(token, WRCK_CSV_SEP);

        // Longitudine
        if (!token) return 0;
        if (!(wreck->longitudine = strtod(token, NULL))) return 0;
        token = next_token;
        next_token = get_next_token(token, WRCK_CSV_SEP);

        // Latitudine
        if (!token) return 0;
        if (!(wreck->latitudine = strtod(token, NULL))) return 0;
    }

    return 1;
}

void show_wreck(WreckData *wreck) {
    printf("%20s: %s\n", "Comune", wreck->comune);
    printf("%20s: %s\n", "Province", wreck->provincia);
    printf("%20s: %s\n", "Region", wreck->regione);
    printf("%20s: %s\n", "Name", wreck->nome);
    printf("%20s: %ju\n", "OSM id", wreck->osm_id);
    printf("%20s: %11.8lf\n", "Longitudine", wreck->longitudine);
    printf("%20s: %11.8lf\n", "Latitudine", wreck->latitudine);
    printf("%20s: <https://www.openstreetmap.org/node/%ju>\n", "OSM link", wreck->osm_id);
    printf("%20s: %s\n", "Insert date", ctime(&wreck->ins_date));
}

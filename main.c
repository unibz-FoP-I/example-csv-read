#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "wreck.h"

#define LINE_BUF_SIZE 2048

int show_csv_wrecks(FILE *fp);

int main(int argc, char const *argv[])
{
    FILE *fp = stdin;
    if (argc > 1) {
        fp = fopen(argv[1], "r");
        if (fp == NULL) {
            perror("fopen");
            exit(EXIT_FAILURE);
        }
    }

    int result = show_csv_wrecks(fp);

    if (argc > 1)
        fclose(fp);

    exit(result);
}

int show_csv_wrecks(FILE *fp) {
    static char line_buf[LINE_BUF_SIZE];
    char *line = NULL;
    size_t len = 0;

    // skip first line (headers)
    if (getline(&line, &len, fp) == -1) {
        free(line);
        return EXIT_FAILURE;
    }

    while (getline(&line, &len, fp) != -1) {
        strncpy(line_buf, line, sizeof(line_buf));
        line_buf[sizeof(line_buf) - 1] = 0;
        WreckData *wreck = csv_row_to_wreck(line_buf);
        if (wreck) {
            puts("------------------------------");
            show_wreck(wreck);
        } else
        {
            fprintf(stderr, "Cannot parse: %s\n", line);
        }
        
    }

    free(line);
    return EXIT_SUCCESS;
}
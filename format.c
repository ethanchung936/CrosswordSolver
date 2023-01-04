/* Purpose: Gather the necessary data to solve a crossword with file IO
 * Author: Ethan Chung
 * Date: December 7, 2022
 * References: N/a
 */

#include "crossword.h"

int get_size(FILE *crossword) {
    int size;
    fscanf(crossword, "%d", &size);
    return size;
}

char *get_crossword(FILE *crossword) {

    fseek(crossword, 0, SEEK_END);
    int len = ftell(crossword);
    fseek(crossword, 0, SEEK_SET);

    char *content = (char*) calloc(len + 1, sizeof(char));
    fread(content, sizeof(char), len, crossword);
    memset(content + len, 0 , 1);

    int size = atoi(strtok(content, " \n"));
    char *array = calloc((size * size + 1), sizeof(char));

    int i = 0;
    char *c = strtok(NULL, " \n");
    while (c != NULL) {
        array[i] = c[0];
        c = strtok(NULL, " \n");
        i++;
    }
    free(content);
    return array;
}

char **get_dictionary(FILE *dictionary, int *number) {
    char **array = malloc(*number * sizeof(char *));

    fseek(dictionary, 0, SEEK_END);
    int len = ftell(dictionary);
    fseek(dictionary, 0, SEEK_SET);

    char *content = (char*) calloc(len + 1, sizeof(char));
    fread(content, sizeof(char), len, dictionary);
    memset(content + len, 0 , 1);

    int i = 0;
    char *c = strtok(content, "\n");
    while (c != NULL && i < *number) {
        array[i] = calloc(strlen(c) + 1, sizeof(char));
        strcpy(array[i], c);
        c = strtok(NULL, "\n");
        i++;
    }
    if (i < *number) {
        *number = i;
        array = realloc(array, *number * sizeof(char *));
    }
    free(content);
    return array;
}

Blank **get_blanks(char *crossword, int size, int *blank_count) {
    Blank **blanks = NULL;
    int blank_size = 0;
    bool prev_blank = false;
    int blank_start = 0;

    // horizontal blanks
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (crossword[i * size + j] != '*') {
                if (prev_blank) {
                    if (blank_size == 0) {
                        blank_size = 2;
                        blank_start = j - 1;
                    }
                    else {
                        blank_size++;
                    }
                }
                prev_blank = true;
            }
            else {
                if (blank_size > 0) {
                    blanks = realloc(blanks, (*blank_count + 1) * sizeof(Blank *));
                    blanks[*blank_count] = malloc(sizeof(Blank));
                    blanks[*blank_count]->length = blank_size;
                    blanks[*blank_count]->x = blank_start;
                    blanks[*blank_count]->y = i;
                    blanks[*blank_count]->vert = false;
                    (*blank_count)++;
                }
                blank_size = 0;
                prev_blank = false;
            }
        }
        if (blank_size > 0) {
                    blanks = realloc(blanks, (*blank_count + 1) * sizeof(Blank *));
                    blanks[*blank_count] = malloc(sizeof(Blank));
                    blanks[*blank_count]->length = blank_size;
                    blanks[*blank_count]->x = blank_start;
                    blanks[*blank_count]->y = i;
                    blanks[*blank_count]->vert = false;
                    (*blank_count)++;
                }
                blank_size = 0;
                prev_blank = false;
    }

    // vertical blanks
    for (int j = 0; j < size; j++) {
        for (int i = 0; i < size; i++) {
            if (crossword[i * size + j] != '*') {
                if (prev_blank) {
                    if (blank_size == 0) {
                        blank_size = 2;
                        blank_start = i - 1;
                    }
                    else {
                        blank_size++;
                    }
                }
                prev_blank = true;
            }
            else {
                if (blank_size > 0) {
                    blanks = realloc(blanks, (*blank_count + 1) * sizeof(Blank *));
                    blanks[*blank_count] = malloc(sizeof(Blank));
                    blanks[*blank_count]->length = blank_size;
                    blanks[*blank_count]->x = j;
                    blanks[*blank_count]->y = blank_start;
                    blanks[*blank_count]->vert = true;
                    (*blank_count)++;
                }
                blank_size = 0;
                prev_blank = false;
            }
        }
        if (blank_size > 0) {
                    blanks = realloc(blanks, (*blank_count + 1) * sizeof(Blank *));
                    blanks[*blank_count] = malloc(sizeof(Blank));
                    blanks[*blank_count]->length = blank_size;
                    blanks[*blank_count]->x = j;
                    blanks[*blank_count]->y = blank_start;
                    blanks[*blank_count]->vert = true;
                    (*blank_count)++;
                }
                blank_size = 0;
                prev_blank = false;
    }
    return blanks;
}
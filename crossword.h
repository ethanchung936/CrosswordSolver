#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <sys/stat.h>

typedef struct {
    int length;
    int x;
    int y;
    bool vert;
} Blank;

int get_size(FILE *crossword);
char *get_crossword(FILE *crossword);
char **get_dictionary(FILE *dictionary, int *number);
Blank **get_blanks(char *crossword, int size, int *blank_count);


bool is_complete(char *crossword);
char *check_word(char *crossword, int size, Blank *blank, char *word);
void solve(char *crossword, int size, char **dictionary, int word_count, Blank **blanks, int blank_count, char ***sol_list, int max_sols);
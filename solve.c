/* Purpose: Functions for solving the crossword
 * Author: Ethan Chung
 * Date: December 7, 2022
 * References: N/a
 */

#include "crossword.h"

bool is_complete(char *crossword) {
    if (strchr(crossword, '0') == NULL) {
        return true;
    }
    return false;
}

char *check_word(char *crossword, int size, Blank *blank, char *word) {
    if (blank->length != strlen(word)) {
        return NULL;
    }
    char *new_copy = calloc((size * size + 1), sizeof(char));
    strcpy(new_copy, crossword);

    if (blank->vert) {
        for (int i = 0; i < blank->length; i++) {
            if (!(crossword[(blank->y + i) * size + blank->x] == '0') && !(crossword[(blank->y + i) * size + blank->x] == word[i])) {
                free(new_copy);
                return NULL;
            }
            else {
                new_copy[(blank->y + i) * size + blank->x] = word[i];
            }
        }
    }
    else {
        for (int i = 0; i < blank->length; i++) {
            if (!(crossword[blank->y * size + blank->x + i] == '0') && !(crossword[blank->y * size + blank->x + i] == word[i])) {
                free(new_copy);
                return NULL;
            }
            else {
                new_copy[blank->y * size + blank->x + i] = word[i];
            }
        }
    }
    return new_copy;
}

void solve(char *crossword, int size, char **dictionary, int word_count, Blank **blanks, int blank_count, char ***sol_list, int max_sols) {
    char *new_copy = NULL;
    static int solutions = 0;
    bool word_removed = false;
    bool found = false;
    for (int i = 0; i < blank_count; i++) {
        found = false;
        for (int j = 0; j < word_count; j++) {
            new_copy = check_word(crossword, size, blanks[i], dictionary[j]);

            if (new_copy != NULL) {
                found = true;
                if (is_complete(new_copy) && solutions < max_sols) {
                    (*sol_list)[solutions] = calloc(strlen(new_copy) + 1, sizeof(char));
                    strcpy((*sol_list)[solutions], new_copy);
                    solutions++;
                }
                else {
                    char **new_dict = malloc((word_count - 1) * sizeof(char *));
                    for (int k = 0; k < word_count; k++) {
                        if (k != j) {
                            if (!word_removed) {
                                new_dict[k] = malloc((strlen(dictionary[k]) + 1) * sizeof(char));
                                strcpy(new_dict[k], dictionary[k]);
                            }
                            else {
                                new_dict[k - 1] = malloc((strlen(dictionary[k]) + 1) * sizeof(char));
                                strcpy(new_dict[k - 1], dictionary[k]);
                            }
                        }
                        else {
                            word_removed = true;
                        }
                    }
                    solve(new_copy, size, new_dict, word_count - 1, blanks + 1, blank_count - 1, sol_list, max_sols);
                    for (int k = 0; k < word_count - 1; k++) {
                        free(new_dict[k]);
                    }
                    free(new_dict);
                }
            }
            free(new_copy);
            word_removed = false;
        }
        if (!found || solutions >= max_sols) {
            return;
        }
    }
}
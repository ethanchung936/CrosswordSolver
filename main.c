/* Purpose: Provide all solutions for a crossword based on a list of words
 * Author: Ethan Chung
 * Date: December 7, 2022
 * References: N/a
 */

#include "crossword.h"

int main(int argc, char **argv) {
    // get user input values and verify them
    if (argc != 5) {
        return 1;
    }
    FILE *crossword_file = fopen(argv[2], "r");
    if (crossword_file == NULL ) {
        return 1;
    }
    FILE *dictionary_file = fopen(argv[1], "r");
    if (dictionary_file == NULL) {
        fclose(crossword_file);
        return 1;
    }
    int max_sols = atoi(argv[3]);
    int word_count = atoi(argv[4]);
    if (max_sols == 0 || word_count == 0) {
        fclose(crossword_file);
        fclose(dictionary_file);
        return 1;
    }
    int size = get_size(crossword_file);
    int blank_count = 0;

    // convert file information into a usable form
    char *crossword = get_crossword(crossword_file);
    char **dictionary = get_dictionary(dictionary_file, &word_count);

    char **sol_list = calloc(max_sols, sizeof(char *));
    Blank **blanks = get_blanks(crossword, size, &blank_count);

    // get all solutions
    solve(crossword, size, dictionary, word_count, blanks, blank_count, &sol_list, max_sols);

    // put solutions into files
    struct stat s = {0};
    if (stat("./Solutions", &s) != 0) {
        #ifdef __linux__
            mkdir("./Solutions", 0777);
        #else
            mkdir("./Solutions");
        #endif
    }    

    char file_name[40] = {0};
    FILE *f;
    for (int i = 0, m = 0; i < max_sols; i++) {
        if (sol_list[i]) {
            sprintf(file_name, "./Solutions/sol%d.txt", m + 1);
            f = fopen(file_name, "w");
            for (int j = 0; j < size; j++) {
                for (int k = 0; k < size; k++) {
                    fprintf(f, "%c", sol_list[m][j * size + k]);
                    if (k < size - 1) {
                        fprintf(f, " ");
                    }
                }
                if (j < size - 1) {
                    fprintf(f, "\n");
                }
            }
            m++;
            fclose(f);
        }
    }
    // free everything
    free(crossword);

    for (int i = 0; i < word_count; i++) {
        free(dictionary[i]);
    }
    free(dictionary);

    for (int i = 0; i < max_sols; i++) {
        if (sol_list[i]) {
            free(sol_list[i]);
        }
    }

    for (int i = 0; i < blank_count; i++) {
        free(blanks[i]);
    }
    free(blanks);
    free(sol_list);
    fclose(crossword_file);
    fclose(dictionary_file);
    return 0;
}


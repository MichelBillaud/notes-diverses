#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#include <ctype.h>
#include <string.h>

#define SHELL_NAME "Shell Zero V0"

#define MAX_LINE_SIZE 200
#define MAX_NB_WORDS 20
#define MAX_WORD_SIZE 20

void print_prompt(int numero)
{
    printf("%d> ", numero);
}

/**
 * Fills an array with the "words" extracted from a line.
 * Words are separated by spaces.
 *
 * @param line a '\n' terminated string
 * @param words an array of strings
*/

int split_line(const char line[],
               char words[][MAX_WORD_SIZE])
{
    int nb_words = 0;
    char *d = NULL;
    bool inside_word = false;

    for (const char *p = line; *p != '\n'; p++) {
        if (inside_word) {
            if (isspace(*p)) {
                // end of a word; add terminator
                *d = '\0';
                inside_word = false;
            } else {
                *d++ = *p; // add char
            }
        } else if (! isspace(*p)) {
            // start of a new word
            inside_word = true;
            d = words[nb_words];
            nb_words += 1;
            *d++ = *p;
        }
    }
    // add terminator to last word if needed
    if (d) {
        *d = '\0';
    }
    return nb_words;
}


void fake_execute_command(int nb_words,
                     char words[][MAX_WORD_SIZE])
{
    printf("Execution of\n");
    for (int i = 0; i < nb_words; i++) {
        printf("- %s\n", words[i]);
    }
}

int main()
{
    printf("--- Hello, this is " SHELL_NAME "!\n");

    int numero = 1; 
    while (true) {
        print_prompt(numero);

        char line[MAX_LINE_SIZE];
        fgets(line, MAX_LINE_SIZE, stdin);

        char words[MAX_NB_WORDS][MAX_WORD_SIZE];
        int nb_words = split_line(line, words);
          if (nb_words == 0) {
            continue;
        }
        if (strcmp(words[0], "exit") == 0) {
            break;
        }
        fake_execute_command(nb_words, words);
        numero += 1;
    }
    printf("Bye!\n");
    return EXIT_SUCCESS;
}

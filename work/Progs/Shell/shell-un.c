#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#include <assert.h>

#include <ctype.h>
#include <string.h>

#define SHELL_NAME "Shell Un V1"

void print_prompt(int numero)
{
    printf("%d> ", numero);
}

/**
 * returns an array of pointers to copies of
 * the "words" extracted from a line.
 *
 * Words in the line are separated by spaces.
 * The array and copies are dynamically allocated. The array
 * contains a NULL pointer after the copies.
 *
 * @param line a nul terminated string
 * @return a dynamically array of pointers do strings
*/

char ** split_line(const char line[])
{
    int nb_args = 0;
    int max_args = 4;
    char **args = malloc(max_args * sizeof(char *));

    const char *start = NULL;

    for (const char *p = line; *p != '\0'; p++) {
        if (start) {
            if (isspace(*p)) { // end of a word detected
                // extend array if needed
                if (nb_args + 1>  max_args) {
                    max_args = 2 * max_args;
                    args = realloc(args, max_args * sizeof(char *));
                }
                // add string copy
                args[nb_args] =  strndup(start, p - start);
                nb_args += 1;
                start = NULL;;
            }
        } else if (! isspace(*p)) { // start of a new word
            start = p;
        }
    }
    assert(start == NULL);
    // no need to worry about the last word, as the line contains a
    // \r ou \n char (which ends the last word) before the nul terminator

    args[nb_args] = NULL;
    return args;
}

void free_array_of_strings(char **args)
{
    for (char **a = args; *a != NULL; a++) {
        free(*a);
    }
    free(args);
}

void fake_execute_command(char ** args)
{
    printf("Execution of\n");
    for (char ** p = args; *p != NULL; p++) {
        printf("- %s\n", *p);
    }
}


void execute_command(char **args)
{
    pid_t child_pid = fork();
    if (child_pid == 0) {
        execvp(args[0], args);
        // if failed 
        perror("execvp failed");
        exit (EXIT_FAILURE);
    }
    waitpid(child_pid, NULL, 0);
}

int main()
{
    char *line = NULL;
    size_t line_size = 0;
    printf("--- Hello, this is " SHELL_NAME "!\n");

    int numero = 1;
    while (true) {
        print_prompt(numero);

        int length = getline(& line, &line_size, stdin);
        if (length < 0) {
            break;
        }
        char **args = split_line(line);
        if (args[0] != NULL) {
            if (strcmp(args[0], "exit") == 0) {
                break;
            } else {
                execute_command(args);
            }
            numero += 1;  // doesn't advance if empty command
        }

        free_array_of_strings(args);
    }
    printf("Bye!\n");
    free(line);
    return EXIT_SUCCESS;
}

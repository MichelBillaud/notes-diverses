#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#include <assert.h>

#include <ctype.h>
#include <string.h>
#include <setjmp.h>


#include "StringArray.h"

#define SHELL_NAME "Shell Deux V1"

void print_prompt(int numero)
{
    printf("%d> ", numero);
}

/**
 * returns a StringArray filled with copies of
 * the "words" extracted from a line.
 *
 * Words in the line are separated by spaces.
 * The array and copies are dynamically allocated.
 *
 * @param line a nul terminated string
 * @return a StringArray
*/

StringArray split_line(const char line[])
{
    StringArray string_array = sa_new();

    const char *start = NULL;

    for (const char *p = line; *p != '\0'; p++) {
        if (start) {
            if (isspace(*p)) { // end of a word detected
                sa_add(& string_array, strndup(start, p - start));
                start = NULL;;
            }
        } else if (! isspace(*p)) { // start of a new word
            start = p;

        }
    }
    assert(start == NULL);
    // no need to worry about the last word, as the line contains a
    // \r ou \n char (which ends the last word) before the nul terminator

    return string_array;
}

void free_array_of_strings(StringArray *sa)
{
    for (size_t i = 0, size = sa_size(sa); i < size; i++) {
        free(sa_array(sa)[i]);
    }
    sa_delete(sa);
}

struct Context {
    jmp_buf main_exit_env;
    jmp_buf main_loop_env;

    int last_retcode;
};

typedef void (*Action)(struct Context *context, const StringArray *words);

#define DEFINE_ACTION(name) void name (struct Context *context, const StringArray *words)

DEFINE_ACTION(do_exit)
{
    longjmp(context->main_exit_env, 0);
}

DEFINE_ACTION(do_help)
{
    printf("Help:\n"
           "<<TODO>>\n");
}

DEFINE_ACTION(do_cd)
{
    if (sa_size(words) == 1) {
        chdir(getenv("HOME"));
    } else {
        chdir(sa_get(words, 1));
    }
}

struct {
    char *name;
    Action action;
} actions[] = {
    {"exit", do_exit},
    {"help", do_help},
    {"cd", do_cd},
    {NULL, NULL}
};

DEFINE_ACTION(do_external_command)
{
    pid_t child_pid = fork();
    if (child_pid == 0) {

        size_t argc = sa_size(words);
        char **args = malloc((argc + 1) * sizeof(char *));
        memcpy(args, sa_array(words), argc * sizeof(char *));
        args[argc] = NULL;

        execvp(args[0], args);
        // if failed
        perror("execvp failed");
        exit (EXIT_FAILURE);
    }
    int status;
    waitpid(child_pid, &status, 0);
    if (WIFEXITED(status)) {
        context->last_retcode = WEXITSTATUS(status);
    } else {
        // interrupted ?
        context->last_retcode = EXIT_FAILURE;
    }
}


void execute_command(struct Context *context, StringArray *words)
{
    Action action = do_external_command;
    char *name = sa_get(words, 0);
    for (size_t i = 0; actions[i].name != NULL; i++) {
        if (strcmp(actions[i].name, name) == 0) {
            action = actions[i].action;
            break;
        }
    }
    (*action)(context, words);
}

// -------------------------------------------------

int main()
{
    struct Context context;
    char *line = NULL;
    size_t line_size = 0;
    printf("--- Hello, this is " SHELL_NAME "!\n");

    int numero = 1;
    int exit_main_loop = setjmp(context.main_exit_env);
    if (exit_main_loop == 0) {
        while (true) {
            print_prompt(numero);

            ssize_t length = getline(& line, &line_size, stdin);
            if (length < 0) {
                break;
            }
            StringArray words = split_line(line);
            if (sa_size(&words) != 0) {
                if (setjmp(context.main_loop_env) == 0) {
                      execute_command(&context, &words);
                } else {
                    printf("command aborted.\n");
                }
                numero += 1;  // doesn't advance if empty command
            }
            free_array_of_strings(&words);
        }
    }
    printf("Bye!\n");
    free(line);
    return EXIT_SUCCESS;
}

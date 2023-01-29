// mini-shell.c

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <string.h>

#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>

#include "split-line.h"
#include "string-array.h"

#define SHELL_NAME "Mini Shell V1"


// all commands receive an array of args
// and return a command_result


struct command_result {
    bool exit_shell;
    int  retcode;
    int  errnum;
};

typedef struct command_result (*COMMAND)(
    const struct string_array *
);

// ------------------------------------------


struct command_result internal_command_exit(
    const struct string_array *args)
{
    int retcode = sa_size(args) == 1
                  ? 0
                  : atoi(sa_get(args, 1));
    return (struct command_result) {
        .exit_shell = true,
        .retcode = retcode,
        .errnum = 0
    };
}

struct command_result internal_command_cd(
    const struct string_array *args)
{
    char *dest = sa_size(args) == 1
                 ? getenv("HOME")
                 : sa_get(args, 1);
    int retcode = chdir(dest);
    return (struct command_result) {
        .exit_shell = false,
        .retcode = retcode,
        .errnum = errno
    };
}


struct command_result internal_command_help(
    const struct string_array *args)
{
    printf("Commands: \n"
           "\ttexit [value] leave the shell\n"
           "\tcd  [dir]     change current directory (default: home)\n"
           "\thelp  | ?     this message\n"
          );
    return (struct command_result) {
        .exit_shell = false,
        .retcode = 0,
        .errnum = 0
    };
}

// -----------------------------------------------------

struct {
    const char *name;
    COMMAND command;
} commands_table[] = {
    {"exit", &internal_command_exit},
    {"cd", &internal_command_cd},
    {"help", &internal_command_help},
    {"?", &internal_command_help},

    {NULL, NULL}
};

// ---------------------------------------------------


struct command_result external_command(
    const struct string_array *args)
{
    pid_t child_pid = fork();
    if (child_pid == 0) {
        // build array
        size_t nb_args = sa_size(args);
        char **a = malloc(sizeof(char *)
                          * (nb_args + 1));
        for (size_t i = 0; i < nb_args; i++) {
            a[i] = sa_get(args, i);
        }
        a[nb_args] = NULL;
        execvp(a[0], a);
        // if failed
        perror("execvp failed");
        exit (EXIT_FAILURE);
    }
    int wait_status;
    waitpid(child_pid, &wait_status, 0);
    return (struct command_result) {
        .exit_shell = false,
        .errnum = 0,
        .retcode = WEXITSTATUS(wait_status)
    };
}

struct command_result execute_command(
    struct string_array *args)
{
    const char * name = sa_get(args, 0);
    COMMAND command = &external_command;
    for (int i = 0; commands_table[i].name != NULL; i++) {
        if (strcmp(commands_table[i].name, name) == 0) {
            // internal command found
            command = commands_table[i].command;
            break;
        }
    }
    // apply command to args
    return (*command)(args);
}


int main()
{
    char *line = NULL;
    size_t line_size = 0;
    printf("--- Hello, this is " SHELL_NAME "!\n");

    int numero = 1;
    for (bool run_loop = true; run_loop; ) {
        printf("%d> ", numero);
        int length = getline(& line, &line_size, stdin);
        if (length < 0) {
            break;
        }
        struct split_line_result slr = split_line(line);
        if (slr.error_message != NULL) {
            printf("Syntax Error at char %zu: %s\n",
                   slr.error_position, slr.error_message);
        } else {
            if (sa_size(& slr.string_array) != 0) {
                struct command_result cr = execute_command(& slr.string_array);
                numero += 1;  // doesn't advance if empty command
                if (cr.errnum != 0) {
                    printf("Error: %s\n", strerror(cr.errnum));
                }
                if (cr.exit_shell) {
                    run_loop = false;
                }
            }
        }
        split_line_result_delete(& slr);
    }

    printf("Bye!\n");
    free(line);
    return EXIT_SUCCESS;
}

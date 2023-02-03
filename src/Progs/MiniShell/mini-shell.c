// mini-shell.c

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <string.h>

#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>

#include "ptr-array.h"
#include "split-line.h"

#define SHELL_NAME "Mini Shell V1.1"


// all commands receive an array of args
// and return a command_result

struct command_result {
    bool exit_shell;
    int  status;
    int  errnum;
};

typedef struct command_result (*FUNCTION)(
    const struct ptr_array *
);

// ------------------------------------------
// table of internal commands
//

struct command_result execute_internal_exit(
    const struct ptr_array *args)
{
    int status = pa_size(args) == 1
                  ? EXIT_SUCCESS
                  : atoi(pa_get(args, 1));
    return (struct command_result) {
        .exit_shell = true,
        .status = status,
        .errnum = 0
    };
}

struct command_result execute_internal_cd(
    const struct ptr_array *args)
{
    char *dest = pa_size(args) == 1
                 ? getenv("HOME")
                 : pa_get(args, 1);
    int status = chdir(dest);
    return (struct command_result) {
        .exit_shell = false,
        .status = status,
        .errnum = errno
    };
}

struct command_result execute_internal_help(
    const struct ptr_array *args)
{
    printf("Commands: \n"
           "\texit [value] leave the shell\n"
           "\tcd  [dir]     change current directory (default: home)\n"
           "\thelp  | ?     this message\n"
          );
    return (struct command_result) {
        .exit_shell = false,
        .status = 0,
        .errnum = 0
    };
}

// -----------------------------------------------------
// table of internal commands :
//     
struct {
    const char *name;
    FUNCTION function;
} commands_table[] = {
    {"exit", &execute_internal_exit},
    {"cd", &execute_internal_cd},
    {"help", &execute_internal_help},
    {"?", &execute_internal_help},

    {NULL, NULL}
};

// ---------------------------------------------------


struct command_result execute_external_command(
    const struct ptr_array *args
)
{
    pid_t child_pid = fork();
    if (child_pid == 0) {
        // build array
        size_t nb_args = pa_size(args);
        char **a = malloc(sizeof(char *)
                          * (nb_args + 1));
        for (size_t i = 0; i < nb_args; i++) {
            a[i] = pa_get(args, i);
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
        .status = WEXITSTATUS(wait_status)
    };
}

struct command_result execute_command(
    struct ptr_array *args
)
{
    const char * name = pa_get(args, 0);
    FUNCTION function = &execute_external_command;
    for (int i = 0; commands_table[i].name != NULL; i++) {
        if (strcmp(commands_table[i].name, name) == 0) {
            // internal command found
            function = commands_table[i].function;
            break;
        }
    }
    // apply function to args
    return (*function)(args);
}

int main()
{
    char *line = NULL;
    size_t line_size = 0;
    int final_status = EXIT_SUCCESS;
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
            if (pa_size(& slr.strings) != 0) {
                struct command_result cr = execute_command(& slr.strings);
                numero += 1;  // doesn't advance if empty command
                if (cr.errnum != 0) {
                    printf("Error: %s\n", strerror(cr.errnum));
                }
                if (cr.exit_shell) {
                    run_loop = false;
                    final_status = cr.status;
                }
            }
        }
        split_line_result_delete(& slr);
    }

    printf("Bye!\n");
    free(line);
    return final_status;
}

// pipeline-general.c

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <assert.h>

struct Step {
    char *pathname;
    char **argv;
};

struct Pipeline {
    int nb_steps;
    struct Step *steps;
};

void execute_pipeline(const struct Pipeline *pipeline)
{
    const int first = 0,
              last = pipeline->nb_steps - 1;

    int input_fd = STDIN_FILENO;

    for (int i = first; i <= last; i++) {
        int pipe_fd[2];
        if (i != last) {
            pipe(pipe_fd);
        }
        if (fork() == 0) {
            // exécution d'un processus fils
            if (i != first) {
                dup2(input_fd, STDIN_FILENO);
                close(input_fd);
            }
            if (i != last) {
                dup2(pipe_fd[1], STDOUT_FILENO);
                close(pipe_fd[0]);
                close(pipe_fd[1]);
            }
            execv(pipeline->steps[i].pathname,
                  pipeline->steps[i].argv);
            assert("lancement fils" && false);
        }
        if (i != first) {
            close(input_fd);
        }
        if (i != last) {
            close(pipe_fd[1]);
            input_fd = pipe_fd[0];
        }
    }

    for (int i = 0; i <= last; i++) {
        wait(NULL);
    }
}




int main()
{

    struct Pipeline pipeline = {
        .nb_steps = 4,
        .steps = (struct Step [])
        {
            {
                .pathname = "/bin/ls",
                .argv = (char *[]) {
                    "ls", "-l", NULL
                }
            }, {
                .pathname = "/bin/grep",
                .argv = (char *[])
                {
                    "grep", "^-", NULL
                }
            }, {
                .pathname = "/bin/cat",
                .argv = (char *[])
                {
                    "cat", NULL
                }
            }, {
                .pathname = "/bin/wc",
                .argv = (char *[])
                {
                    "wc", "-l", NULL
                }
            },
        }
    };

    printf("Exécution " __FILE__ "\n");
    printf("Nombre de fichiers dans le répertoire =\n");
    execute_pipeline(& pipeline);
    printf("# fin\n");
    return EXIT_SUCCESS;
}

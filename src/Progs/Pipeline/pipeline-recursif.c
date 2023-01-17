// pipeline-recursif.c

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


void execute_steps(int nb_steps, struct Step steps[nb_steps])
{
    assert(nb_steps > 0);
    if (nb_steps == 1) {
        pid_t single_command_pid = fork();
        if (single_command_pid == 0) {
            execv(steps[0].pathname,
                  steps[0].argv);
            assert("lancement commande seule" && false);
        }
        waitpid(single_command_pid, NULL, 0);
    } else {
        int pipe_fd[2];
        pipe(pipe_fd);
        pid_t first_command_pid = fork();
        if (first_command_pid == 0) {
            dup2(pipe_fd[1], STDOUT_FILENO);
            close(pipe_fd[0]);
            close(pipe_fd[1]);
            execv(steps[0].pathname,
                  steps[0].argv);
            assert("lancement première commande" && false);
        }

        dup2(pipe_fd[0], STDIN_FILENO);
        close(pipe_fd[0]);
        close(pipe_fd[1]);
        execute_steps(nb_steps-1, steps + 1);
        waitpid(first_command_pid, NULL, 0);
    }
}


void execute_pipeline(const struct Pipeline *pipeline)
{
    execute_steps(pipeline->nb_steps,
                  pipeline->steps);

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

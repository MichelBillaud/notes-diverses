#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>


#define MAX_STEPS 6
#define MAX_ARGS 5
#define MAX_STRING_LEN 10

struct Step {
    int argc;
    char *argv[MAX_ARGS];
};

struct Pipeline {
    int nb_steps;
    struct Step steps[MAX_STEPS];
};


void execute_pipeline(const struct Pipeline *pipeline)
{

    int fd[2];
    int last = pipeline->nb_steps - 1;
    int in = 0;
    for (int i = 0; i <= last; i++) {
        printf("# step %d\n", i);
        const struct Step *s = & pipeline->steps[i];

        if (i == last) {
            fd[1] = 1;
        } else {
            pipe(fd);
            fprintf(stderr, "- pipe {%d, %d)\n", fd[0], fd[1]);
        }
        pid_t pid = fork();
        if (pid == 0) {
            fprintf(stderr, "> redirection entree %d, sortie %d\n", in, fd[1]);
            dup2(in, 0);
            dup2(fd[1], 1);
            fprintf(stderr,  "> exec %s\n", s->argv[0]);
            execvp(s->argv[0], s->argv);
        }
        if (i != 0) {
            fprintf(stderr, "- fermeture in %d\n", in );
            close(in);
        }
        if (i != last) {
            fprintf(stderr, "- fermeture out %d\n", fd[1]);
            close(fd[1]);
        }
        in = fd[0];
    }
    for (int i = 0; i <= last; i++) {
        wait(NULL);
    }
}


int main()
{
    printf("Hello, world\n");

    struct Pipeline pipeline = {
        .nb_steps = 6,
        .steps = {
            { .argc = 2, .argv = {"ls", "-l"} },
            { .argc = 1, .argv = {"cat"} },
            { .argc = 2, .argv = {"grep", "^-"} },
            { .argc = 1, .argv = {"cat"} },
            { .argc = 1, .argv = {"cat"} },
            {
                .argc = 2, .argv = {"wc", "-l"}
            }
        }
    };

    execute_pipeline(& pipeline);
    return EXIT_SUCCESS;
}

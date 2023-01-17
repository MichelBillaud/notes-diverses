// demo-fork.c

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <assert.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>

#include <fcntl.h>

void execute_task()
{
    char *path = "/bin/tr";
    char *arguments[] = { "tr", "a-z", "A-Z",  NULL};
    int fd = open("demo-fork.c", O_RDONLY);
    dup2(fd, 0);
    close(fd);
    execv(path, arguments);
    // en cas de problème pour lancer tr
    perror("erreur lancement commande tr");
    exit(EXIT_FAILURE);
}

void explain_child_status(int child_status)
{
    printf("# La commande s'est terminée ");
    if (WIFEXITED(child_status)) {
        printf("par exit(%d)\n", WEXITSTATUS(child_status));
    } else if (WIFSIGNALED(child_status)) {
        printf("par la réception du signal %d\n", WTERMSIG(child_status));
    } else {
        printf("pour une raison x ou y.\n");
    }
}

int main(int argc, char *argv[])
{
    pid_t child_pid = fork();
    if (child_pid == 0) {
        execute_task();
        assert("on ne revient jamais ici" && false);
    }
    int child_status;
    waitpid(child_pid, &child_status, 0);

    explain_child_status(child_status);
    exit(EXIT_SUCCESS);
}

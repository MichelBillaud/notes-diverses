// demo-pipe.c

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>

#include <fcntl.h>


int main(int argc, char *argv[])
{
    int fd[2];
    
    pipe(fd);

    pid_t date_pid = fork();
    if (date_pid == 0) {
        dup2(fd[1], STDOUT_FILENO);
        close(fd[0]);
        close(fd[1]);
        execv("/bin/date", (char *[]){"date", NULL}); 
        perror("échec lancement de date");
        exit(EXIT_FAILURE);
    }
    
    pid_t tr_pid = fork();
    if (tr_pid == 0) {
        dup2(fd[0], STDIN_FILENO);
        close(fd[0]);
        close(fd[1]);
        execv("/bin/tr", (char *[]){"tr", "a-z", "A-Z", NULL}); 
        perror("échec lancement de tr");
        exit(EXIT_FAILURE);
    }

    close(fd[0]);
    close(fd[1]);
    waitpid(date_pid, NULL, 0);
    waitpid(tr_pid, NULL, 0);
    
    exit(EXIT_SUCCESS);
}

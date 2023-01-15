// demo-pipeline.c

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <assert.h>

int main()
{
    printf("Exécution " __FILE__ "\n");
    printf("Nombre de fichiers dans le répertoire =\n");

    int input_fd = STDIN_FILENO;
    int pipe_fd[2];

    pipe(pipe_fd);                    // création pipe T1

    pid_t a_pid = fork();
    if (a_pid == 0) {
        // le processus A écrit dans T1
        dup2(pipe_fd[1], STDOUT_FILENO);
        close(pipe_fd[0]);
        close(pipe_fd[1]);
        execv("/bin/ls", (char *[]) {
            "ls", "-l", NULL
        });
        assert("lancement premier fils" && false);
    }
    close(pipe_fd[1]);          // fermeture desc. écriture de T1

    input_fd = pipe_fd[0];      // sauvegarde descripteur lecture T1
    pipe(pipe_fd);              // création pipe T2

    pid_t b_pid = fork();
    if (b_pid == 0) {
        // le processus B lit dans T1, écrit dans T2
        dup2(input_fd, STDIN_FILENO);
        dup2(pipe_fd[1], STDOUT_FILENO);
        close(input_fd);
        close(pipe_fd[0]);
        close(pipe_fd[1]);
        execv("/bin/grep", (char *[]) {
            "grep", "^-", NULL
        });
        assert("lancement second fils" && false);
    }
    close(input_fd);             // descripteur lecture T1
    close(pipe_fd[1]);           // descripteur écriture T2

    input_fd = pipe_fd[0];       // sauvegarde descripteur lecture T2
    pipe(pipe_fd);               // création pipe T3

    pid_t c_pid = fork();
    if (c_pid == 0) {
        // le processus C lit dans T2, écrit dans T3
        dup2(input_fd, STDIN_FILENO);
        dup2(pipe_fd[1], STDOUT_FILENO);
        close(input_fd);         // desc lecture T2
        close(pipe_fd[0]);       // desc lecture T3
        close(pipe_fd[1]);       // desc écriture T3
        execv("/bin/cat", (char *[]) {
            "cat", NULL
        });
        assert("lancement troisième fils" && false);
    }
    close(input_fd);        // desc lecture  T2
    close(pipe_fd[1]);      // desc écriture T3

    input_fd = pipe_fd[0];  // sauvegarde descripteur lecture T3


    pid_t d_pid = fork();
    if (d_pid == 0) {
        // le processus C lit dans T3
        dup2(input_fd, STDIN_FILENO);
        close(input_fd);         // desc lecture T3
        execv("/bin/wc", (char *[]) {
            "wc", "-l", NULL
        });
        assert("lancement quatrième fils" && false);
    }

    close(input_fd);

    waitpid(a_pid, NULL, 0);
    waitpid(b_pid, NULL, 0);
    waitpid(c_pid, NULL, 0);
    waitpid(d_pid, NULL, 0);

    printf("# fin\n");
    return EXIT_SUCCESS;
}

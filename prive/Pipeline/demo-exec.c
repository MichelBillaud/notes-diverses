// demo-exec.c

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
    printf("# lancement " __FILE__ "\n");

    char *path = "/bin/ls";
    char *arguments[] = { "ls", "/tmp", NULL};

    execv(path, arguments);

    perror("échec lancement");
    exit(EXIT_FAILURE);

}

// demo-exec-dup.c

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main()
{
    printf("# lancement " __FILE__ "\n");

    char *path = "/bin/tr";
    char *arguments[] = { "tr", "a-z", "A-Z",  NULL};
    
    int fd = open("demo-exec-dup.c", O_RDONLY);
    dup2(fd, 0);
    close(fd);
    
    execv(path, arguments);
    close(fd);

    perror("échec lancement");
    exit(EXIT_FAILURE);

}

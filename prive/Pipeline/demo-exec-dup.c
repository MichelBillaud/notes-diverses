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

    int file_fd = open("demo-exec-dup.c", O_RDONLY);
    dup2(file_fd, STDOUT_FILENO);
    close(file_fd);
    
    execv("/bin/tr", (char *[]){ "tr", "a-z", "A-Z",  NULL} );

    perror("échec lancement");
    exit(EXIT_FAILURE);

}

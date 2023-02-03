// demo-boucle.c

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

int main()
{
    char *line = NULL;
    size_t line_size = 0;
    printf("--- Démo Boucle\n");
    printf("tapez exit pour arrêter\n");

    int numero = 1;
    for (bool run_loop = true; run_loop; ) {
        printf("%d> ", numero);
        int length = getline(& line, &line_size, stdin);
        if (length < 0) {
            break;
        }
        printf("=> %s\n", line);
        if (strncmp(line, "exit", 4) == 0) {
            run_loop = false;
        }
        numero += 1;
    }

    printf("Bye!\n");
    free(line);
    return EXIT_SUCCESS;
}

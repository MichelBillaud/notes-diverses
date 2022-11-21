// my-assert.c

#include <stdio.h>
#include <stdlib.h>

#define my_assert(condition) { \
	if(!(condition)) { \
	   fprintf(stderr, "Dans %s ligne %d (fonction %s) l'assertion '%s' est fausse\n.",\
	   	__FILE__, __LINE__, __func__, #condition); \
       exit(1); \
	}\
}

int main()
{
    printf("Début\n");
    my_assert(2+2 == 4);
    my_assert(2+3 == 6);
    my_assert(3+3 == 6);
    printf("Fin\n");
}


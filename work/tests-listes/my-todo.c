// my-todo.c

#include <stdio.h>
#include <stdlib.h>

#define TODO(message) { \
	   fprintf(stderr,  "Dans %s ligne %d (fonction %s) "\
                        "code manquant : %s.", \
	   	__FILE__, __LINE__, __func__, #message ); \
       exit(1); \
	}


int foo() {
    TODO("bla")
}
int fib(int n)
{
    if (n <=1) {
        return n;
    } else {
        TODO("valeurs > à 2");
    }
}

int main()
{
    printf("fib(0) = %d\n", fib(0));
    printf("fib(1) = %d\n", fib(1));
    printf("fib(2) = %d\n", fib(2));
}


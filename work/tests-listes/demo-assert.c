// demo-assert.c 

#include <stdio.h>
#include <assert.h>

int main() 
{
    printf("Début\n");
    assert(2+2 == 4);
    assert(2+3 == 6);
    assert(3+3 == 6);
    printf("Fin\n");
}


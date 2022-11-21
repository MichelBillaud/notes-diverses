// fib.c - tests fonction fibonacci

#include <stdio.h>
#include <assert.h>


int fib(int n) {
    return n;         // évidemment incorrect
}

void tests_fib() {
    assert("cas de base" && fib(0) == 0);
    assert("cas de base" && fib(1) == 1);
    assert("valeur suivante" && fib(2) == 1);
       
}

int main() {
    tests_fib();
    return 0;
}
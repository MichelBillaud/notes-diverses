// StringArray.c

#include <stdlib.h>
#include <memory.h>
#include "StringArray.h"

#define STRINGARRAY_MIN_CAPACITY 8

StringArray sa_new()
{
    return (StringArray) {
        .size = 0,
        .capacity = STRINGARRAY_MIN_CAPACITY,
        .array = malloc(STRINGARRAY_MIN_CAPACITY
                        * sizeof(char *))
    };
}

void sa_delete(StringArray *sa)
{
    sa->size = 0;
    sa->capacity = 0;
    free(sa->array);
    sa->array = NULL;
}

void sa_add(StringArray *sa, char *string)
{
    if (sa->size == sa->capacity) {
        sa->capacity *= 2;
        sa->array = realloc(sa->array,
                            sa->capacity * sizeof(char *));
    }
    sa->array[sa->size++] = string;
}


size_t sa_size(const StringArray *sa)
{
    return sa->size;
}

char ** sa_array(const StringArray *sa)
{
    return sa->array;
}


char * sa_get(const StringArray *sa, size_t index)
{
    return sa->array[index];
}
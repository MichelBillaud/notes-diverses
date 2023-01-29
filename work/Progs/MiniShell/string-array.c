// string-array.c

#include <stdlib.h>
#include <memory.h>

#include "string-array.h"

#ifndef STRING_ARRAY_MIN_CAPACITY
    #define STRING_ARRAY_MIN_CAPACITY 8
#endif

struct string_array sa_new() {
    return (struct string_array) {
        .size = 0,
        .capacity = STRING_ARRAY_MIN_CAPACITY,
        .array = malloc(STRING_ARRAY_MIN_CAPACITY
                        * sizeof(char *))
    };
}

void sa_init(struct string_array *sa)
{
    *sa = sa_new();
}

void sa_delete(struct string_array *sa)
{
    sa->size = 0;
    sa->capacity = 0;
    free(sa->array);
    sa->array = NULL;
}

void sa_add(struct string_array *sa, char *string)
{
    if (sa->size == sa->capacity) {
        sa->capacity *= 2;
        sa->array = realloc(sa->array,
                            sa->capacity * sizeof(char *));
    }
    sa->array[sa->size++] = string;
}

size_t sa_size(const struct string_array *sa)
{
    return sa->size;
}

char * sa_get(const struct string_array *sa, size_t index)
{
    return sa->array[index];
}
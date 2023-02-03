// ptr-array.c

#include <stdlib.h>
#include <memory.h>

#include "ptr-array.h"

#ifndef PTR_ARRAY_MIN_CAPACITY
    #define PTR_ARRAY_MIN_CAPACITY 8
#endif

struct ptr_array pa_new() {
    return (struct ptr_array) {
        .size = 0,
        .capacity = PTR_ARRAY_MIN_CAPACITY,
        .array = malloc(PTR_ARRAY_MIN_CAPACITY
                        * sizeof(void *))
    };
}

void pa_init(struct ptr_array *pa)
{
    *pa = pa_new();
}

void pa_delete(struct ptr_array *pa)
{
    pa->size = 0;
    pa->capacity = 0;
    free(pa->array);
    pa->array = NULL;
}

void pa_add(struct ptr_array *pa, void *ptr)
{
    if (pa->size == pa->capacity) {
        pa->capacity *= 2;
        pa->array = realloc(pa->array,
                            pa->capacity * sizeof(void *));
    }
    pa->array[pa->size++] = ptr;
}

size_t pa_size(const struct ptr_array *pa)
{
    return pa->size;
}

void * pa_get(const struct ptr_array *pa, size_t index)
{
    return pa->array[index];
}

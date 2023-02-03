// ptr-array.h 

#ifndef PTR_ARRAY_H
#define PTR_ARRAY_H

#include <stddef.h>

struct ptr_array {
    size_t size;
    size_t capacity;
    void **array;
};

void pa_init(struct ptr_array *pa); 
struct ptr_array pa_new();

void pa_delete(struct ptr_array *pa);
void pa_add(struct ptr_array *pa, void *ptr);

size_t pa_size(const struct ptr_array *pa);
void * pa_get(const struct ptr_array *pa, size_t index);

#endif
// stringarray.h 

#ifndef STRINGARRAY_H
#define STRINGARRAY_H

#include <stddef.h>

struct string_array {
    size_t size;
    size_t capacity;
    char **array;
};

void sa_init(struct string_array *sa); 
struct string_array sa_new();

void sa_delete(struct string_array *sa);
void sa_add(struct string_array *sa, char *string);

size_t sa_size(const struct string_array *sa);
char * sa_get(const struct string_array *sa, size_t index);

#endif
// StringArray.h 

#ifndef STRINGARRAY_H
#define STRINGARRAY_H
#include <stdint.h>

typedef struct StringArray {
    size_t size;
    size_t capacity;
    char **array;
} StringArray;

StringArray sa_new(void);
void sa_delete(StringArray *sa);
void sa_add(StringArray *sa, char *string);

size_t sa_size(const StringArray *sa);
char ** sa_array(const StringArray *sa);
char * sa_get(const StringArray *sa, size_t index);

#endif
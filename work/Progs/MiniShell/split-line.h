#ifndef SPLIT_LINE_H
#define SPLIT_LINE_H

#include "stringarray.h"

struct split_line_result {
    struct string_array string_array;
    const char *error_message;
    size_t error_position;
};

struct split_line_result split_line(const char line[]);
void split_line_result_delete(struct split_line_result *r);


#endif
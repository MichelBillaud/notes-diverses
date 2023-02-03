// split-line.h

#ifndef SPLIT_LINE_H
#define SPLIT_LINE_H

#include "ptr-array.h"

struct split_line_result {
    struct ptr_array strings;
    const char *error_message;
    size_t error_position;
};

struct split_line_result split_line(const char line[]);
void split_line_result_delete(struct split_line_result *r);

#endif
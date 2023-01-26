// split-line.c

#include <malloc.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

#include "split-line.h"


static bool is_ending_char(char c)
{
    return (c == '#') || (c == '\0');
}

static bool is_word_char(char c)
{
    return !( isspace(c) || is_ending_char(c));
}

struct split_line_result split_line(const char line[])
{
    struct split_line_result r = {
        .error_message = NULL,
        .error_position = 0,
        .string_array = sa_new()
    };

    int i = 0;

    for (;;) {
        // ignore spaces
        while(isspace(line[i])) {
            i++;
        };
        if (is_ending_char(line[i])) {
            break;
        }
        int start_index = i;
        do {
            i += 1;
        } while(is_word_char(line[i]));

        sa_add(& r.string_array,
               strndup(& line[start_index], i - start_index));
    }

    return r;
}


void split_line_result_delete(struct split_line_result *r)
{
    const size_t n = sa_size(& r->string_array);
    for (size_t i = 0; i < n; i++) {
        free(sa_get(& r->string_array, i));
    }
    sa_delete(& r->string_array);

}
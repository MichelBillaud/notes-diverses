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
        .strings = pa_new()
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

        pa_add(& r.strings,
               strndup(& line[start_index],
                       i - start_index));
    }

    return r;
}

void split_line_result_delete(struct split_line_result *r)
{
    const size_t n = pa_size(& r->strings);
    for (size_t i = 0; i < n; i++) {
        free(pa_get(& r->strings, i));
    }
    pa_delete(& r->strings);
}
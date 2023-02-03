// test-split-line.c

#include <stdio.h>
#include <string.h>

#include <assert.h>

#include "split-line.h"

void test_empty(const char line[])
{
    struct split_line_result r = split_line(line);

    assert("empty line has no words" &&
           pa_size(& r.strings) == 0);
    split_line_result_delete(& r);
}

void basic_test()
{
    printf("- basic_test()\n");
    char line[] = "  one  two three";
    struct split_line_result r = split_line(line);
    assert("example size is 3"
           && pa_size(&r.strings) == 3);
    assert("first word is 'one'" &&
            strcmp(pa_get(&r.strings, 0), "one") == 0);
    assert("second word is 'two'" &&
            strcmp(pa_get(&r.strings, 1), "two") == 0);
    assert("third word is 'three'" &&
            strcmp(pa_get(&r.strings, 2), "three") == 0);
    split_line_result_delete(& r);

}

void test_empty_lines()
{
    printf("- test_empty_lines()\n");
    test_empty("");
    test_empty("\n");
    test_empty("    \n");
}

int main()
{
    printf("# tests split-line\n");
    test_empty_lines();
    basic_test();
    printf("Ok\n");
}
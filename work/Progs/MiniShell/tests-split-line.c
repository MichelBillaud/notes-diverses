// test-split-line.c

#include <stdio.h>
#include <string.h>

#include <assert.h>

#include "stringarray.h"
#include "split-line.h"

void test_empty(const char line[])
{
    struct split_line_result r = split_line(line);

    assert("empty line has no words" &&
           sa_size(& r.string_array) == 0);
    split_line_result_delete(& r);
}

void test_1()
{
    printf("- test_1()\n");
    char line[] = "  one  two three";
    struct split_line_result r = split_line(line);
    assert("example size is 3"
           && sa_size(&r.string_array) == 3);
    assert("first word is 'one'" &&
            strcmp(sa_get(&r.string_array, 0), "one") == 0);
    assert("second word is 'two'" &&
            strcmp(sa_get(&r.string_array, 1), "two") == 0);
    assert("third word is 'three'" &&
            strcmp(sa_get(&r.string_array, 2), "three") == 0);
    split_line_result_delete(& r);

}

void test_empty_lines()
{
    printf("- tests empty_lines\n");
    test_empty("");
    test_empty("\n");
    test_empty("    \n");
}

int main()
{
    printf("# tests split-line\n");
    test_empty_lines();
    test_1();
    printf("Ok\n");
}
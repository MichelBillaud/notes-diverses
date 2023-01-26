// tests-stringarray.c

#include <stdio.h>
#include <assert.h>

#include "stringarray.h"

void test_1()
{
	printf("- test_1()\n");
    struct string_array sa = sa_new();

    assert("new StringArray size is zero" &&
           sa_size(&sa) == 0);

    char *s[21] = {
        "zero", "one", "two", "three", "four",
        "five", "six", "seven", "eight", "nine",
        "ten", "eleven", "twelve", "thirteen", "fourteen",
        "fifteen", "sixteen", "seventeen", "eighteen", "nineteen",
        "twenty"
    };

    for (size_t i = 0; i < 21; i++) {
        sa_add(&sa, s[i]);
        assert("adding increases size"
               && sa_size(&sa) == i+1);
        assert("data is present at end"
               && sa_get(&sa, i) == s[i]);
    }

    for (size_t i = 0; i < 21; i++) {
        assert("all added data is there"
               && sa_get(&sa, i) == s[i]);
    }

    sa_delete(&sa);

}

int main()
{
    printf("# Tests StringArray\n");
    test_1();
    printf("Ok\n");
}

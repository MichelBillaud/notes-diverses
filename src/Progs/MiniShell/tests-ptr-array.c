// tests-ptr-array.c

#include <stdio.h>
#include <assert.h>

#include "ptr-array.h"

void basic_test()
{
	printf("- basic_test()\n");
    struct ptr_array sa = pa_new();

    assert("new PtrArray size is zero" &&
           pa_size(&sa) == 0);

    char *s[21] = {
        "zero", "one", "two", "three", "four",
        "five", "six", "seven", "eight", "nine",
        "ten", "eleven", "twelve", "thirteen", "fourteen",
        "fifteen", "sixteen", "seventeen", "eighteen", "nineteen",
        "twenty"
    };

    for (size_t i = 0; i < 21; i++) {
        pa_add(&sa, s[i]);
        assert("adding increases size"
               && pa_size(&sa) == i+1);
        assert("data is present at end"
               && pa_get(&sa, i) == s[i]);
    }

    for (size_t i = 0; i < 21; i++) {
        assert("all added data is there"
               && pa_get(&sa, i) == s[i]);
    }

    pa_delete(&sa);

}

int main()
{
    printf("# Tests ptr_array\n");
    basic_test();
    printf("Ok\n");
}

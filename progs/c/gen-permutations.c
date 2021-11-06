#include <stdio.h>
#include <stdbool.h>


bool get_first_permutation(int array[], int size);
bool get_next_permutation(int array[], int size);

void print_array(int array[], int size);

int main()
{
    int array[4];
    int number = 0;
    for (bool exists = get_first_permutation(array, 4);
            exists;
            exists = get_next_permutation(array, 4)) {
        number += 1;
        printf("%4d : ", number);
        print_array(array, 4);
        printf("\n");
    }

}

void print_array(int array[], int size)
{
    for (int i = 0; i < size; i++) {
        printf("%3d", array[i]);
    }
}

bool get_first_permutation(int array[], int size)
{
    if (size <= 0) {
        return false;
    }
    for (int i = 0; i < size; i++) {
        array[i] =  i;
    }
    return true;
}

void swap(int *pa, int *pb)
{
    int tmp = *pa;
    *pa = *pb;
    *pb = tmp;
}

bool get_next_permutation(int array[], int size)
{
    int suffix_start = size-1;
    while (suffix_start > 0
            &&  array[suffix_start - 1] >= array[suffix_start]) {
        suffix_start --;
    }
    if (suffix_start == 0) {
        return false;
    }
    int index = size -1;
    while (array[suffix_start - 1] > array[index]) {
        index --;
    }
    swap (& array[suffix_start - 1], & array[index]);
    for (int left = suffix_start, right = size - 1;
            left < right;
            left++, right-- ) {
        swap (& array[left], &array[right]);
    }

    return true;
}

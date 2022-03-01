#define _GNU_SOURCE 1

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int comparator_r(const void *v1, const void *v2, void *context) {
	const int *p1 = v1, *p2 = v2;
	int *array = context;
	return array[*p1] - array[*p2];
}

void test_qsort_r() 
{
	int array[9] = { 66, 11, 44, 22, 88, 55, 77, 99, 33};
	int perm[9]  = {  0,  1,  2,  3,  4,  5,  6,  7,  8};
	qsort_r(perm, 9, sizeof(array[0]), comparator_r, array);

	for (int i = 0; i < 9; i++) {
		printf("[%d]=%d ", perm[i], array[perm[i]]);
	}
	printf("\n");
} 


void * comparator_context;

int comparator(const void *v1, const void *v2) {
	const int *p1 = v1, *p2 = v2;
	int *array = comparator_context;
	return array[*p1] - array[*p2];
}

void test_qsort() 
{
	int array[9] = { 66, 11, 44, 22, 88, 55, 77, 99, 33};
	int perm[9]  = {  0,  1,  2,  3,  4,  5,  6,  7,  8};
	comparator_context = array;
	qsort(perm, 9, sizeof(array[0]), comparator);

	for (int i = 0; i < 9; i++) {
		printf("[%d]=%d ", perm[i], array[perm[i]]);
	}
	printf("\n");
} 

void selint_sort(int array[], size_t size)
{
	for (size_t i = 0; i < size; i++) {
		size_t m = i;
		for (size_t j = i + 1; j < size; j++) {
			if (array[j] < array[m] ) {
				m = j;
			}
		}
		if (m != i) {
			int tmp = array[i];
			array[i] = array[m];
			array[m] = tmp;
		}
	}
}

void test_selint() 
{
	printf("# test selint\n");
	int array[9] = { 66, 11, 44, 22, 88, 55, 77, 99, 33};
	comparator_context = array;
	selint_sort(array, 9);
	for (int i = 0; i < 9; i++) {
		printf("%d ", array[i]);
	}
	printf("\n");
}

void selint_param_sort(int array[], size_t size, 
		int (*comparator)(const int, const int))
{
	for (size_t i = 0; i < size; i++) {
		size_t m = i;
		for (size_t j = i + 1; j < size; j++) {
			if (comparator(array[j], array[m]) < 0 ) {
				m = j;
			}
		}
		if (m != i) {
			int tmp = array[i];
			array[i] = array[m];
			array[m] = tmp;
		}
	}
}

int descending(int a, int b) {
	return b - a;
}

void test_selint_param() 
{
	printf("# test selint_param\n");
	int array[9] = { 66, 11, 44, 22, 88, 55, 77, 99, 33};
	comparator_context = array;
	selint_param_sort(array, 9, descending);
	for (int i = 0; i < 9; i++) {
		printf("%d ", array[i]);
	}
	printf("\n");
}

void selint_sort_r(int array[], size_t size, 
		int (*comparator)(const int, const int, void *),
		void *context)
{
	for (size_t i = 0; i < size; i++) {
		size_t m = i;
		for (size_t j = i + 1; j < size; j++) {
			if (comparator(array[j], array[m], context) < 0 ) {
				m = j;
			}
		}
		if (m != i) {
			int tmp = array[i];
			array[i] = array[m];
			array[m] = tmp;
		}
	}
}
int comp_r(const int i1, const int i2, void *context) {
	int *array = context;
	return array[i1] - array[i2];
}

void test_selint_sort_r()
{
	printf("# test_selint_sort_r\n");
	int array[9] = { 66, 11, 44, 22, 88, 55, 77, 99, 33};
	int perm[9]  = {  0,  1,  2,  3,  4,  5,  6,  7,  8};
	selint_sort_r(perm, 9, comp_r, array);

	for (int i = 0; i < 9; i++) {
		printf("[%d]=%d ", perm[i], array[perm[i]]);
	}
	printf("\n");
}


int main()
{
	printf("Hello, world\n");
	test_qsort_r();
	test_qsort();

	test_selint();
	test_selint_param();
	test_selint_sort_r();
	
	return EXIT_SUCCESS;
}

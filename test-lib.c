#include <stdio.h>
#include <stdlib.h>

void print_num(int n)
{
	printf("%d\n", n);
}

void print_double(double n)
{
	printf("%f\n", n);
}

int *give_memory(int size)
{
	return malloc(size);
}

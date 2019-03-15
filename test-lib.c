#include <stdio.h>
#include <stdlib.h>

void print_num(int n)
{
	printf("%d\n", n);
}

int *give_memory(int size)
{
	return malloc(size);
}

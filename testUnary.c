int **x;
int *y;
int z;
int a;

int main(void)
{
	z = 3;

	y = &z;
	*y = 4;

	print_num(z);
}

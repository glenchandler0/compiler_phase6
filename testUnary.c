int **x;
int *y;
int z;
int a;

int main(void)
{
	z = 3;

	y = &a;	
	x = &y;

	*x = &z;

	print_num(**x);
}

int x;
int y;

int foo2(void)
{
	return 2;
}

int foo(int y)
{
	return y * y;
}

int main(void)
{
	x = 3;
	x = foo(foo(x)); 
	print_num(x);
}

int x;

int foo(void)
{
	x = 2;
	return x;
	x = 3;
}

int main(void)
{
	foo();
	print_num(x);
}

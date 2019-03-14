int x;
int y;

int foo2(void)
{
	return 2;
}

int foo(void)
{
	int y;	
	y = 4;	
	return y * y;
}

int main(void)
{
	x = 3;
	x = foo(); 
	print_num(x);
	y = foo() + foo() + foo() + foo();
	print_num(y);
}

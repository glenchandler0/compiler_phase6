int x;

int main(void)
{
	int y;
	int z;

	y = 100; 
	z = 3;

	x = y > z;
	print_num(x);
	x = y < x;
	print_num(x);
	x = y <= z;
	print_num(x);
	x = z == z;
	print_num(x);
	x = z != z;
	print_num(x);
	x = y >= z;
	print_num(x);	
}

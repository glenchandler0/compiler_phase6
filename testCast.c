int x;
double y;
char z;

int main(void)
{
	y = 3.85391;
	z = (int)y; 
	y = (double)z;
	
	x = (int)y;
	z = (char)x;
	y = (double)x;

	x = (int)y;

	print_num(x);
}

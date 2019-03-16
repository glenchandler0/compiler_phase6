int x;
double y;
char z;

int main(void)
{
	x = 1000;
	y = (double)x;
	x = (int)y;

	print_num(x);
}

/* math.c */
int num;

int testfun(int input)
{
	return input;
}

int main(void)
{
    double x, y, z;
    double a, b, c, d, e;

    x = 100;
    y = 30;
    z = 2;

    a = x + y + z;
    b = x - y - z;
    c = x * y * z;
    d = x / y + z;
    e = x / y - z;

num = a;
print_num(num);
num = b;
print_num(num);
num = c;
print_num(num);
num = d;
print_num(num);
num = e;
print_num(num);
}


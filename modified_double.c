/* math.c */
double num;

double testfun(double input)
{
	return input + input;
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
num = testfun(num);
}


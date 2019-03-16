int x;

int recurse(int x)
{
	if(x == 3)
		return 1;

	recurse(x + 1);
}

int main(void)
{
	x = recurse(0);
	printf("%d\n", x);
}

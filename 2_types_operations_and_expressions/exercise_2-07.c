#include <stdio.h>

unsigned int invert(unsigned int x, int p, int n);

unsigned int invert(unsigned int x, int p, int n)
{
	if (n > p)
		n = p + 1;
	unsigned int mask = ~(~0u << n)
	                    << (p - n + 1); // n 1s at position p, rest 0
	return x ^ mask;
}

int main(void)
{
	unsigned int x = 255;              // …011111111
	unsigned result = invert(x, 5, 3); // …011000111 = 199
	printf("%d\n", result);
	return 0;
}

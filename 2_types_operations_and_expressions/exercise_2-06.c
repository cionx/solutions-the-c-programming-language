#include <stdio.h>

unsigned int setbits(unsigned int x, int p, int n, unsigned int y);

unsigned int setbits(unsigned int x, int p, int n, unsigned int y)
{
	if (n > p)
		n = p + 1;
	unsigned int mask = ~(~0u << n) << (p - n + 1); // n 1s at position p, rest 0
	return (x & ~mask) | (y & mask);
}

int main(void)
{
	unsigned int x = 255; // …011111111
	unsigned int y = 0;
	printf("%u\n", setbits(x, 4, 3, y)); // …011100011 = 227
}

#include <stdio.h>

unsigned int setbits(unsigned int x, int p, int n, unsigned int y);

unsigned int setbits(unsigned int x, int p, int n, unsigned int y)
{
	if (n > p)
		n = p + 1;
	unsigned int ones = ~(~0u << n); // Right-aligned block of n many 1s.
	unsigned int x_removed = x & ~(ones << (p + 1 - n));
	unsigned int y_rightmost = y & ones;
	return x_removed | (y_rightmost << (p + 1 - n));
}

int main(void)
{
	unsigned int x = 240;                // …011110000
	unsigned int y = 15;                 // …000001111
	printf("%u\n", setbits(x, 6, 5, y)); // …010111100 = 188
}

#include <stdio.h>

unsigned int rightrot(unsigned int x, int n);

unsigned int rightrot(unsigned int x, int n)
{
	int width = 8 * sizeof(unsigned int);
	// UINT_WIDTH from limits.h doesn't work for some reason.
	n %= width;

	unsigned int mask = ~(~0u << n); // n many 1s right-adjusted
	unsigned int head = x & ~mask;
	unsigned int tail = x & mask;
	return (head >> n) | (tail << (width - n));
}

int main(void)
{
	unsigned int x = 1;
	int width = 8 * sizeof(unsigned int);
	for (int i = 0; i <= width; ++i)
		printf("%2d  %u\n", i, rightrot(x, i));

	return 0;
}

#include <stdio.h>

int bitcount(unsigned int x);
int faster_bitcount(unsigned int x);

int bitcount(unsigned int x)
{
	int b;

	for (b = 0; x != 0; x >>= 1)
		if (x & 01)
			b++;

	return b;
}

int faster_bitcount(unsigned int x)
{
	int b = 0;
	while (x != 0) {
		x &= (x - 1);
		++b;
	}

	return b;
}

int main(void)
{
	unsigned int limit = 10000000;
	for (unsigned int i = 0; i < limit; ++i) {
		int b = bitcount(i);
		int f = faster_bitcount(i);
		if (b != f) {
			printf("Error for %u: %d should be %d", i, f, b);
			return 1;
		}
	}

	printf("Correct result for all numbers from 0 to %u.\n", limit);
	return 0;
}

#include <stdio.h>

#define swap(t, x, y)  {t tmp = x; x = y; y = tmp;}

int main(void)
{
	int x = 1;
	int y = 2;
	printf("Before: x = %d, y = %d.\n", x, y);
	swap(int, x, y)
	printf("After:  x = %d, y = %d.\n", x, y);
}

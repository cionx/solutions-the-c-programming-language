#include <limits.h>
#include <stdio.h>

void itoa(int n, char s[]);
int helper(int n, char s[]);

void itoa(int n, char s[])
{
	/* Handle this special case by hand. */
	if (n == 0) {
		s[0] = '0';
		s[1] = '\0';
	}

	/* Make n negative and set the sign. */
	int i = 0;
	if (n < 0)
		s[i++] = '-';
	else
		n = -n;

	helper(n, s + i);       /* pointer arithmetic */
}

int helper(int n, char s[]) /* returns the length of the computed string. */
{
	if (n == 0) {
		return 0;
	}
	char digit = -(n % 10) + '0';
	int pos = helper(n / 10, s);
	s[pos] = digit;
	s[pos + 1] = '\0';
	return pos + 1;
}

int main(void)
{
	int nums[] = {0, 123, -123, INT_MAX, INT_MIN};
	char s[100];
	for (int i = 0; i < 5; ++i) {
		itoa(nums[i], s);
		printf("%d becomes \"%s\"\n", nums[i], s);
	}
	return 0;
}

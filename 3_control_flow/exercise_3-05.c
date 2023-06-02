#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

void itoa(int n, char s[], int b);
char digit(int n);
void reverse(char s[]);

/* itoa: convert n to characters in s with respect to base b */
void itoa(int n, char s[], int b)
{
	int i = 0;
	bool sign = (n < 0);

	/* Calculate digits using negative modulo until there is no overflow.
	 * This also takes care of the digit for n = 0.
	 */
	do {
		int mod = n % b;
		if (mod < 0)
			mod = -mod;
		s[i++] = digit(mod);
		n /= b;
	} while (n < 0 && -n < 0); /* Should always fail. */
	/* Make n non-negative. */
	if (n < 0)
		n = -n;
	/* Generate the digits in reverse order. */
	for (; n > 0; n /= b)
		s[i++] = digit(n % b);
	if (sign)
		s[i++] = '-';
	s[i] = '\0';

	reverse(s);
}

/* digits: n is required to be non-negative.
 * The output is '0', '1', ..., '9', 'A', 'B', ...
 */
char digit(int n)
{
	if (0 <= n && n <= 9)
		return (char) n + '0';
	else if (10 <= n)
		return (char) (n - 10) + 'A';
	return -1;
}

/* reverse: reverse string s in place */
void reverse(char s[])
{
	for (int i = 0, j = (int) strlen(s) - 1; i < j; i++, j--) {
		char c = s[i];
		s[i] = s[j];
		s[j] = c;
	}
}

int main(void)
{
	int numbers[] = {123, -123, 0, INT_MAX, INT_MIN};
	int length = 5;
	char s[100];

	for (int i = 0; i < length; ++i) {
		itoa(numbers[i], s, 2);
		printf("%d becomes \"%s\"\n", numbers[i], s);
	}

	return 0;
}

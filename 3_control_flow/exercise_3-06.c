#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

void itoa(int n, char s[], int width);
void reverse(char s[]);

/* itoa: convert n to characters in s with minimal width */
void itoa(int n, char s[], int width)
{
	int i = 0;
	bool sign = (n < 0);

	/* Calculate digits using negative modulo until there is no overflow.
	 * This also takes care of the digit for n = 0.
	 */
	do {
		int mod = n % 10;
		if (mod < 0)
			mod = -mod;
		s[i++] = (char) mod + '0';
		n /= 10;
		--width;
	} while (n < 0 && -n < 0); /* Should always fail. */
	/* Make n non-negative. */
	if (n < 0)
		n = -n;
	/* Generate the digits in reverse order. */
	for (; n > 0; n /= 10, --width)
		s[i++] = n % 10 + '0';
	if (sign) {
		s[i++] = '-';
		--width;
	}
	for (; width > 0; --width)
		s[i++] = ' ';
	s[i] = '\0';

	reverse(s);
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
		itoa(numbers[i], s, 6);
		printf("%d becomes \"%s\"\n", numbers[i], s);
	}

	return 0;
}

#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

void itob(int n, char s[], int b);
char digit(int n);
void reverse(char s[]);

/* itob(n, s, b): convert n to characters in s with base b */
void itob(int n, char s[], int b)
{
	bool negative = (n < 0);
	if (n > 0)
		n = -n;

	int i = 0;
	do {
		s[i++] = digit(-(n % b));
	} while ((n /= b) != 0);

	if (negative)
		s[i++] = '-';

	s[i] = '\0';
	reverse(s);
}

/* digit(n): n is required to be non-negative.
 * The output is '0', '1', ..., '9', 'A', 'B', ...
 * Should only be used for 0 <= n <= 35
 */
char digit(int n)
{
	if (0 <= n && n <= 9)
		return (char) n + '0';
	else if (10 <= n)
		return (char) (n - 10) + 'A';
	return -1;
}

/* reverse(s): reverse the string s in place */
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
		itob(numbers[i], s, 2);
		printf("%d becomes \"%s\"\n", numbers[i], s);
	}

	return 0;
}

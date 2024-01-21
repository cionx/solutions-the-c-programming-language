#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

void itoa(int n, char s[], int width);
void reverse(char s[]);

/* itoa(n, s, w): convert n to characters in s with minimal width w */
void itoa(int n, char s[], int width)
{
	bool negative = (n < 0);
	if (n > 0)
		n = -n;

	int i = 0;
	do {
		s[i++] = -(n % 10) + '0';
		--width;
	} while ((n /= 10) != 0);
	if (negative)
		s[i++] = '-';

	for (; width > 0; --width)
		s[i++] = ' ';

	s[i] = '\0';
	reverse(s);
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
		itoa(numbers[i], s, 6);
		printf("%d becomes \"%s\"\n", numbers[i], s);
	}

	return 0;
}

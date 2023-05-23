#include <stdbool.h>
#include <stdio.h>

int htoi(char s[]);
bool whitespace(char c);
bool hexa_start(char string[], int position);
int hexa_value(char c);

int htoi(char s[])
{
	/* We regard the occurrence of no digits as the empty sum. */
	if (s[0] == '\0')
		return 0;
	int i = 0;

	/* Ignore leading whitespace. */
	while (whitespace(s[i]))
		++i;

	/* Support negative numbers. */
	bool negative = false;
	if ((negative = (s[i] == '-')))
		++i;

	/* Ignore whitespace between minus sign and 0x/0X. */
	while (whitespace(s[i]))
		++i;

	if (hexa_start(s, i))
		i += 2;

	int sum = 0;
	for (; s[i] != '\0'; i++) {
		sum *= 16;
		sum += hexa_value(s[i]);
	}

	if (negative)
		return -sum;
	else
		return sum;
}

/* Checks if a character is inline whitespace. */
bool whitespace(char c)
{
	return c == ' ' || c == '\t';
}

/* Checks for 0x/0X at the given position. */
bool hexa_start(char s[], int i)
{
	return (s[i] == '0') && (s[i + 1] == 'x' || s[i + 1] == 'X');
}

/* The character needs to be a valid hexadecimal digit.
 * Otherwise, -1 is returned.
 */
int hexa_value(char c)
{
	if ('0' <= c && c <= '9')
		return c - '0';
	else if ('a' <= c && c <= 'f')
		return 10 + c - 'a';
	else if ('A' <= c && c <= 'F')
		return 10 + c - 'A';

	return -1;
}

int main(void)
{
	char s[] = "    -0x1f";
	printf("\"%s\" becomes %d\n", s, htoi(s));

	return 0;
}

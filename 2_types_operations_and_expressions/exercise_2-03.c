#include <stdbool.h>
#include <stdio.h>

bool ishexdigit(char c);
int hexvalue(char c);
int htoi(const char s[]);

bool ishexdigit(char c)
{
	return ('0' <= c && c <= '9') || ('a' <= c && c <= 'f') ||
	       ('A' <= c && c <= 'F');
}

int hexvalue(char c)
{
	if ('0' <= c && c <= '9')
		return c - '0';
	if ('a' <= c && c <= 'f')
		return c - 'a' + 10;
	if ('A' <= c && c <= 'F')
		return c - 'A' + 10;
	return -1;
}

int htoi(const char s[])
{
	int result = 0;
	int sign = 1;

	int i = 0;

	/* Gobble up leading whitespace. */
	while (s[i] == ' ')
		++i;
	/* Determine the sign. */
	if (s[i] == '-') {
		sign = -1;
		++i;
	}
	/* Gobble up whitespace again. */
	while (s[i] == ' ')
		++i;
	/* Ignore optional 0x or 0X. */
	if (s[i] == '0' && (s[i + 1] == 'x' || s[i + 1] == 'X'))
		i += 2;
	/* Convert the remaining digits. */
	for (; ishexdigit(s[i]); ++i) {
		result *= 16;
		result += hexvalue(s[i]);
	}
	/* Finally, return the result. */
	return sign * result;
}

int main(void)
{
	const char *strings[24] = {"1f",     "1F",    "0x1f",    "0X1F",   " 1f",
	                           " 1F",    " 0x1f", " 0X1F",   "-1f",    "-1F",
	                           "-0x1f",  "-0X1F", " -1f",    " -1F",   " -0x1f",
	                           " -0X1F", "- 1f",  "- 1F",    "- 0x1f", "- 0X1F",
	                           " - 1f",  " - 1F", " - 0x1f", " - 0X1F"};
	for (int i = 0; i < 24; ++i)
		printf("\"%s\" \t %d\n", strings[i], htoi(strings[i]));
	return 0;
}

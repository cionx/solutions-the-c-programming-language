#include <stdio.h>

int strrindex(char s[], char t[]);

/* strrindex(s, t): find the rightmost occurrence of t in s */
int strrindex(char s[], char t[])
{
	/* Find the end of s. */
	int i = 0;
	while (s[i] != '\0')
		++i;

	for (; i >= 0; --i) {
		/* Check if s[i] start a substring equal to t. */
		int j = i;
		int k = 0;
		while (s[j] == t[k] && t[k] != '\0')
			++j, ++k;
		if (t[k] == '\0')
			return i;
	}

	return -1;
}

int main(void)
{
	char s[] = "012345678901234567890123456789";

	printf("\"%s\" in \"%s\" at %d\n", "89012", s, strrindex(s, "89012"));
	printf("\"%s\" in \"%s\" at %d\n", "89", s, strrindex(s, "89"));
	printf("\"%s\" in \"%s\" at %d\n", "98", s, strrindex(s, "98"));
	return 0;
}

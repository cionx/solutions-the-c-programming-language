/* getline: read a line into s, return length */
#include <stdio.h>

int getaline(char s[], int lim)
{
	int c;
	char *start = s;

	for (; s - start < lim - 1 && (c = getchar()) != EOF && c != '\n'; ++s)
		*s = c;
	if (c == '\n') {
		*s = c;
		++s;
	}
	*s = '\0';
	return s - start;
}

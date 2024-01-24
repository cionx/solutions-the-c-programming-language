#include <stdbool.h>
#include <stdio.h>

bool strend(char const *s, char const *t);

/* strend(s, t): checks if t as the end of s */
bool strend(char const *s, char const *t)
{
	const char *u = s, *v = t;
	while (*u != '\0')
		++u;
	while (*v != '\0')
		++v;

	while (s < u && t < v && *u == *v)
		--u, --v;
	return v == t && *u == *v;
}

int main(void)
{
	char *s = "abcdef";
	char *t = "def";
	char *u = "cef";
	char *v = "fedcba";
	char *w = "abcdefg";
	printf("\"%s\" ends in \"%s\": %d\n", s, s, strend(s, s));
	printf("\"%s\" ends in \"%s\": %d\n", s, t, strend(s, t));
	printf("\"%s\" ends in \"%s\": %d\n", s, u, strend(s, u));
	printf("\"%s\" ends in \"%s\": %d\n", s, v, strend(s, v));
	printf("\"%s\" ends in \"%s\": %d\n", s, w, strend(s, w));
}

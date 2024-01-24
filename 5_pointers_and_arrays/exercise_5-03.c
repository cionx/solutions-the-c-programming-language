#include <stdio.h>

/* strcat(s, t): appends t to s */
void strcat(char *s, const char *t)
{
	while (*s != '\0')
		++s;
	while ((*s = *t) != '\0')
		++s, ++t;
}

int main(void)
{
	char s[10] = "abc";
	char t[] = "def";

	printf("s = \"%s\", t = \"%s\"", s, t);
	strcat(s, t);
	printf(" becomes \"%s\"\n", s);

	return 0;
}

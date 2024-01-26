#include <ctype.h>
#include <stdio.h>

int atoi(char s[]);

/* atoi: convert s to integer; pointer version */
int atoi(char s[])
{
	int n, sign;

	for (; isspace(*s); ++s)    /* skip white space */
		;
	sign = (*s == '-') ? -1 : 1;
	if (*s == '+' || *s == '-') /* skip sign */
		s++;
	for (n = 0; isdigit(*s); ++s)
		
		n = 10 * n + (*s - '0');
	return sign * n;
}

int main(void)
{
	char *strings[] = {"123", "-123", "0", "-0"};
	for (int i = 0; i < 4; ++i)
		printf("\"%s\" becomes %d.\n", strings[i], atoi(strings[i]));
}

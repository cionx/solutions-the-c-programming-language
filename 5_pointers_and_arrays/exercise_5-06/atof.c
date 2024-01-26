#include <ctype.h>
#include <stdio.h>

double atof(char s[]);

/* atof: convert string s to double; pointer version */
double atof(char s[])
{
	double val, power;
	int sign;

	for (; isspace(*s); ++s) /* skip white space */
		;
	sign = (*s == '-') ? -1 : 1;
	if (*s == '+' || *s == '-')
		s++;
	for (val = 0.0; isdigit(*s); s++)
		val = 10.0 * val + (*s - '0');
	if (*s == '.')
		s++;
	for (power = 1.0; isdigit(*s); s++) {
		val = 10.0 * val + (*s - '0');
		power *= 10.0;
	}
	return sign * val / power;
}

int main(void)
{
	char *strings[] = {"123",     "-123",     "0",    "-0",
	                   "123.456", "-123.456", ".456", "-.456"};
	for (int i = 0; i < 8; ++i)
		printf("\"%s\" becomes %g.\n", strings[i], atof(strings[i]));
}

#include "exercise_4-02.h"
#include <ctype.h>

/* atof: convert string s to double */
double my_atof(char s[])
{
	double value, power;
	int i, sign, expsign, exponent;

	for (i = 0; isspace(s[i]); ++i) /* skip whitespace */
		;
	sign = (s[i] == '-') ? -1 : 1;
	if (s[i] == '+' || s[i] == '-')
		++i;
	for (value = 0.0; isdigit(s[i]); ++i)
		value = 10 * value + (s[i] - '0');

	if (s[i] == '.')
		++i;
	for (power = 1.0; isdigit(s[i]); ++i) {
		value = 10.0 * value + (s[i] - '0');
		power *= 10.0;
	}

	exponent = 0;
	if (s[i] == 'e' || s[i] == 'E') {
		++i;
		expsign = (s[i] == '-') ? -1 : 1;
		if (s[i] == '+' || s[i] == '-')
			++i;
		for (; isdigit(s[i]); ++i) {
			exponent = 10 * exponent + (s[i] - '0');
		}
		exponent *= expsign;
	}

	value = sign * value / power;
	for (; exponent > 0 && value != value / 10; --exponent)
		value *= 10;
	for (; exponent < 0 && value != value * 10; ++exponent)
		value /= 10;

	return value;
}

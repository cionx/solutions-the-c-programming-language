#include <ctype.h>
#include <stdio.h>

double my_atof(char s[]);

/* atof: convert string s to double */
double my_atof(char s[])
{
	double value = 0.0;
	double power = 1.0;
	int sign = 1;

	int i = 0;
	/* skip whitespace */
	while (isspace(s[i]))
		++i;
	/* optional: leading sign */
	if (s[i] == '-') {
		sign = -1;
	}
	if (s[i] == '-' || s[i] == '+')
		++i;
	/* the integer part */
	for (; isdigit(s[i]); ++i)
		value = 10.0 * value + (double) (s[i] - '0');

	/* the fractional part */
	if (s[i] == '.')
		++i;
	for (; isdigit(s[i]); ++i) {
		value = 10.0 * value + (double) (s[i] - '0');
		power *= 10.0;
	}

	/* optional: the exponent */
	int exponent = 0;
	int expsign = 1;
	if (s[i] == 'e' || s[i] == 'E') {
		++i;
		if (s[i] == '-')
			expsign = -1;
		if (s[i] == '+' || s[i] == '-')
			++i;
		for (; isdigit(s[i]); ++i) {
			exponent = 10 * exponent + (s[i] - '0');
		}
		exponent *= expsign;
	}

	value = sign * value / power;
	for (; exponent > 0 && 10 * value != value; --exponent)
		value *= 10;
	for (; exponent < 0 && value / 10 != value; ++exponent)
		value /= 10;

	return value;
}

/* Testing */
int main(void)
{
	char *tests[] = {/* 123 */
	                 "123", "+123", "-123",
	                 /* 0 */
	                 "0", "+0", "-0",
	                 /* 123.456 */
	                 "123.456", "+123.456", "-123.456",
	                 /* 0.123 */
	                 "0.123", "+0.123", "-0.123",
	                 /* .123 */
	                 ".123", "+.123", "-.123",
	                 /* 123e4 */
	                 "123e4", "+123e4", "-123e4",    // e
	                 "123e+4", "+123e+4", "-123e+4", // e+
	                 "123e-4", "+123e-4", "-123e-4", // e-
	                 /* 0e4 */
	                 "0e4", "+0e4", "-0e4",    // e
	                 "0e+4", "+0e+4", "-0e+4", // e+
	                 "0e-4", "+0e-4", "-0e-4", // e-
	                 /* 123.456e7 */
	                 "123.456e7", "+123.456e7", "-123.456e7",    // e
	                 "123.456e+7", "+123.456e+7", "-123.456e+7", // e+
	                 "123.456e-7", "+123.456e-7", "-123.456e-7", // e-
	                 /* 123.456e789 */
	                 "123.456e789", "+123.456e789", "-123.456e789",    // e
	                 "123.456e+789", "+123.456e+789", "-123.456e+789", // e+
	                 "123.456e-789", "+123.456e-789", "-123.456e-789", // e-
	                 /* 0e789 */
	                 "0e789", "+0e789", "-0e789",    // e
	                 "0e+789", "+0e+789", "-0e+789", // e+
	                 "0e-789", "+0e-789", "-0e-789", // e-
	                 /* 1e123456789 */
	                 "1e123456789", "+1e123456789", "-1e123456789",    // e
	                 "1e+123456789", "+1e+123456789", "-1e+123456789", // e+
	                 "1e-123456789", "+1e-123456789", "-1e-123456789", // e-
	                 /* 123.456-3 */
	                 "123.456-3", "+123.456-3", "-123.456-3",
	                 /* 123.456+3 */
	                 "123.456+3", "+123.456+3", "-123.456+3"};
	int testCount = 75;

	for (int i = 0; i < testCount; ++i)
		printf("\"%s\" becomes %g\n", tests[i], my_atof(tests[i]));

	return 0;
}

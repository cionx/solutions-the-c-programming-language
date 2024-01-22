# Exercise 4-2

> Extend `atof` to handle scientific notation of the form `123.45e-6` where a floating-point number may be followed by `e` or `E` and optionally signed exponent.

---

We extend the given code by also reading a scientific exponent part.
Afterwards we multiply by 10 or divide by 10 as often as the exponent dictates, via a loop.

However, we need to be careful:
for large exponents, the loop would take far too long.
However, for large exponents (positive or negative), we will eventually arrive at one of the values `inf`, `-inf`, `0` or `-0`.
We can then stop the loop, no matter how much of the exponent remains.
More explicitly, we stop the loop whenever the calculated value stabilizes.

```c
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
```

We also want to point out a possible problem, which we avoided with our code:
suppose that we had used the following additional code instead (not using the `if`-block):
```c
int exponent = 0;
int expsign = 1;
if (s[i] == 'e' || s[i] == 'E')
	++i;
if (s[i] == '-')
	expsign = -1;
if (s[i] == '+' || s[i] == '-')
	++i;
for (; isdigit(s[i]); ++i) {
	exponent = 10 * exponent + (s[i] - '0');
exponent *= expsign;
```
A string like `1-2` would then have been mistakenly interpreted as `1e-2`.

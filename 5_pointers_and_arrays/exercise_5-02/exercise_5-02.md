# Exercise 5-2
> Write `getfloat,` the floating-point analog of `getint.`
> What type does `getfloat` return as its function value?

---

We can use the same approach as in `atof`:
```c
int getdouble(double *px)
{
	int c, sign;
	double power;

	while (isspace(c = getch())) /* skip white space */
		;
	if (!isdigit(c) && c != EOF && c != '.' && c != '+' && c != '-') {
		ungetch(c);
		return 0;
	}
	/* sign */
	sign = (c == '-') ? -1 : 1;
	if (c == '-' || c == '+')
		c = getch();
	/* integer part */
	for (*px = 0.0; isdigit(c); c = getch())
		*px = 10 * *px + (c - '0');
	/* decimal part */
	if (c == '.')
		c = getch();
	power = 1.0;
	for (; isdigit(c); c = getch()) {
		*px = 10 * *px + (c - '0');
		power *= 10;
	}
	/* the overall result */
	*px = sign * *px / power;
	if (c != EOF)
		ungetch(c);
	return c;
}
```

We test this function as follows:
```c
int main(void)
{
	double x = 0;
	while (getdouble(&x) != EOF)
		printf("Read %g\n", x);
	return 0;
}
```
It seems to work:
```
123
Read 123
123.456
Read 123.456
-.123
Read -0.123
```

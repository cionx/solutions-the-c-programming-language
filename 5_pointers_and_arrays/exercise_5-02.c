/* MAIN */

#include <stdio.h>

int getdouble(double *);

int main(void)
{
	double x = 0;
	while (getdouble(&x) != EOF)
		printf("Read %g\n", x);
	return 0;
}

/* GETINT */

#include <ctype.h>

int getch(void);
void ungetch(int);

/* getint(pn) get next integer from input into *pn */
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

/* BUFFER */

#define BUFSIZE 100

int buf[BUFSIZE]; /* buffer for ungetch */
int bufp = 0;     /* next free position in buf */

int getch(void)   /* get a (possibly pushed back) character */
{
	return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c) /* push character back on input */
{
	if (bufp >= BUFSIZE)
		printf("ungetch: too many characters\n");
	else
		buf[bufp++] = c;
}

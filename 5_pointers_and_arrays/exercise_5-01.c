/* MAIN */

#include <stdio.h>

int getint(int *);

int main(void)
{
	int n = 0;
	while (getint(&n) != EOF)
		printf("Read %d\n", n);
	return 0;
}

/* GETINT */

#include <ctype.h>

int getch(void);
void ungetch(int);

/* getint(pn) get next integer from input into *pn */
int getint(int *pn)
{
	int c, sign;

	while (isspace(c = getch())) /* skip white space */
		;
	if (!isdigit(c) && c != EOF && c != '+' && c != '-') {
		ungetch(c);
		return 0;
	}
	sign = (c == '-') ? -1 : 1;
	if (c == '-' || c == '+') {
		c = getch();
		if (!isdigit(c)) {
			ungetch(c);
			ungetch((sign == -1) ? '-' : '+');
			return 0;
		}
	}
	for (*pn = 0; isdigit(c); c = getch())
		*pn = 10 * *pn + (c - '0');
	*pn *= sign;
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

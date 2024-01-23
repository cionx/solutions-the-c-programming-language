/* THE MAIN CALCULATOR */

#include <stdio.h>
#include <stdlib.h> /* for atof() */

#define MAXOP  100  /* max size of operand or operator */
#define NUMBER '0'  /* signal that a number was found */
#define LAST   '_'  /* signal for the last printed value */
#define SAVE   '#'  /* signal for saving a variable */
#define LOAD   'a'  /* signal for reading a variable */

int getop(char[]);
void push(double);
double pop(void);
double top(void);

/* reverse Polish calculator */
int main(void)
{
	int type;
	char s[MAXOP];

	double op2;

	double last_printed;

	int var_name;
	double vars[26];
	for (int i = 0; i < 26; ++i)
		vars[i] = 0.0;

	while ((type = getop(s)) != EOF) {
		switch (type) {
			case NUMBER:
				push(atof(s));
				break;
			case '+':
				push(pop() + pop());
				break;
			case '*':
				push(pop() * pop());
				break;
			case '-':
				op2 = pop();
				push(pop() - op2);
				break;
			case '/':
				op2 = pop();
				if (op2 != 0.0)
					push(pop() / op2);
				else
					printf("error: zero division\n");
				break;
			case LAST:
				push(last_printed);
				break;
			case SAVE:
				var_name = s[0];
				vars[var_name - 'a'] = top();
				break;
			case LOAD:
				var_name = s[0];
				push(vars[var_name - 'a']);
				break;
			case '\n':
				printf("\t%.8g\n", last_printed = pop());
				break;
			default:
				printf("error: unknown command %s\n", s);
				break;
		}
	}

	return 0;
}

/* THE STACK */

#define MAXVAL 100  /* maximum depth of val stack */

int sp = 0;         /* next free stack position */
double val[MAXVAL]; /* value stack */

/* push(f): push f onto value stack */
void push(double f)
{
	if (sp < MAXVAL)
		val[sp++] = f;
	else
		printf("error: stack full, can't push %g\n", f);
}

/* pop(): pop and return top value from stack */
double pop(void)
{
	if (sp > 0)
		return val[--sp];
	else {
		printf("error: stack empty\n");
		return 0.0;
	}
}

/* GETOP */

#include <ctype.h>

int getch(void);
void ungetch(int);

/* getop(s): get next operator or numeric operand */
int getop(char s[])
{
	int i, c;

	while ((s[0] = c = getch()) == ' ' || c == '\t') /* skip whitespace */
		;
	s[1] = '\0';

	if (c == '_')
		return LAST; /* last printed number */

	if (c == '#') {
		c = getch();
		if ('a' <= c && c <= 'z') {
			s[0] = c;
			return SAVE;
		}
		else {
			printf("error: missing variable name after #\n");
			ungetch(c);
		}
	}

	if ('a' <= c && c <= 'z')
		return LOAD;

	if (!isdigit(c) && c != '.')
		return c;   /* not a number */

	i = 0;
	if (isdigit(c)) /* collect integer part */
		while (isdigit(s[++i] = c = getch()))
			;
	if (c == '.')   /* collect fraction part */
		while (isdigit(s[++i] = c = getch()))
			;
	s[i] = '\0';
	if (c != EOF)
		ungetch(c);
	return NUMBER;
}

double top(void)
{
	double value = pop();
	push(value);
	return value;
}

/* BUFFER */

#define BUFSIZE 100

char buf[BUFSIZE]; /* buffer for ungetch */
int bufp = 0;      /* next free position in buf */

int getch(void)    /* get a (possibly pushed back) character */
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

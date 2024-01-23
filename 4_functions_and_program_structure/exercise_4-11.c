/* THE MAIN CALCULATOR */

#include <stdio.h>
#include <stdlib.h> /* for atof() */

#define MAXOP  100  /* max size of operand or operator */
#define NUMBER '0'  /* signal that a number was found */

int getop(char[]);
void push(double);
double pop(void);

/* reverse Polish calculator */
int main(void)
{
	int type;
	char s[MAXOP];
	double op2;

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
			case '\n':
				printf("\t%.8g\n", pop());
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
#include <stdbool.h>

/* getop(s): get next operator or numeric operand */
int getop(char s[])
{
	int i, c;

	static int buffer = ' ';      /* Dummy value. */
	static bool buffered = false; /* Nothing buffered before the first call. */

	if (buffered) {
		c = buffer;
		buffered = false;
	}
	else
		c = getchar();

	while ((s[0] = c) == ' ' || c == '\t') /* skip whitespace */
		c = getchar();
	s[1] = '\0';

	if (!isdigit(c) && c != '.')
		return c;   /* not a number */

	i = 0;
	if (isdigit(c)) /* collect integer part */
		while (isdigit(s[++i] = c = getchar()))
			;
	if (c == '.')   /* collect fraction part */
		while (isdigit(s[++i] = c = getchar()))
			;
	s[i] = '\0';
	if (c != EOF) {
		buffer = c;
		buffered = true;
	}
	return NUMBER;
}

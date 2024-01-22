/* THE MAIN CALCULATOR */

#include <stdio.h>
#include <stdlib.h> /* for atof() */

#define MAXOP  100  /* max size of operand or operator */
#define NUMBER '0'  /* signal that a number was found */

int getop(char[]);
void push(double);
double pop(void);
double top(void);
void duplicate(void);
void swap(void);
void clear(void);
void view(void);
void remove_linebreak(void);

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
			case 't':
				printf("\t%.8g\n", top());
				remove_linebreak();
				break;
			case 'd':
				printf("duplicate stack head ...\n");
				duplicate();
				remove_linebreak();
				break;
			case 's':
				printf("swap the two top stack entries...\n");
				swap();
				remove_linebreak();
				break;
			case 'c':
				printf("clear the stack...\n");
				clear();
				remove_linebreak();
				break;
			case 'v':
				view();
				remove_linebreak();
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

double top(void)
{
	double value = pop();
	push(value);
	return value;
}

void duplicate(void)
{
	double value = top();
	push(value);
}

void swap(void)
{
	double value1 = pop();
	double value2 = pop();
	push(value1);
	push(value2);
}

void clear(void)
{
	sp = 0;
}

void view(void)
{
	for (int i = 0; i < sp; ++i)
		printf("%g ", val[i]);
	printf("\n");
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

void remove_linebreak(void)
{
	int c = getch();
	if (c != '\n')
		ungetch(c);
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

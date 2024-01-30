/* THE MAIN CALCULATOR */

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h> /* for atof() */
#include <string.h> /* for strcmp */

enum argtype { error, number, addition, subtraction, multiplication, division };

enum argtype getargtype(char *s);
void push(double);
double pop(void);

/* reverse Polish calculator */
int main(int argc, char *argv[])
{
	enum argtype type;
	double op2;

	while (--argc > 0) {
		char *argument = *++argv;
		type = getargtype(argument);
		switch (type) {
			case number:
				push(atof(argument));
				break;
			case addition:
				push(pop() + pop());
				break;
			case multiplication:
				push(pop() * pop());
				break;
			case subtraction:
				op2 = pop();
				push(pop() - op2);
				break;
			case division:
				op2 = pop();
				if (op2 == 0.0) {
					printf("division by zero detected\n");
					return -1;
				}
				push(pop() / op2);
				break;
			case error:
				printf("Cannot handle argument %s\n", argument);
				break;
		}
	}
	printf("Result: %g\n", pop());
	return 0;
}

bool isnumber(char *s);

enum argtype getargtype(char *expr)
{
	if (strcmp(expr, "+") == 0)
		return addition;
	if (strcmp(expr, "*") == 0)
		return multiplication;
	if (strcmp(expr, "-") == 0)
		return subtraction;
	if (strcmp(expr, "/") == 0)
		return division;
	if (isnumber(expr))
		return number;
	return error;
}

/* a very naive implementation; has many false positives */
bool isnumber(char *s)
{
	if (!isdigit(*s) && *s != '.' && *s != '+' && *s != '-')
		return false;
	if (*s == '+' || *s == '-')
		++s;
	while (isdigit(*s))
		++s;
	if (*s == '.')
		++s;
	while (isdigit(*s))
		++s;
	return (*s == '\0');
}

/* THE STACK */

#define MAXVAL 100         /* maximum depth of val stack */

static int sp = 0;         /* next free stack position */
static double val[MAXVAL]; /* value stack */

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

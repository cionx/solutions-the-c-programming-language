# Exercise 5-10

> Write the program `expr,` which evaluates a reverse Polish expression from the command line, where each operator or operand is a separate argument.
> For example,
> ```text
> expr 2 3 4 + *
> ```
> evaluates 2 × (3 + 4).

---

We will follow the approach from Section 4.3.
More precisely, we will
- iterate through the passed arguments in `argv` (ignoring `argv[0]`),
- decide for each argument its “type”
- act according to the type.

Our `main` function ends up as follows:
```c
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
```

The function `getargtyp` looks as follows:
```c
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
```
Our implementation of `isnumber` is kept naive for simplicity.
```c
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
```

The code for the stack of intermediate results can be copied from Section 4.3.
```c
/* THE STACK */

#define MAXVAL 100  /* maximum depth of val stack */

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
```

We can now test our program:
```text
$ ./a.out 2 3 4 + "*"
14
```
(We had to use `"*"` instead of simply `*` because our terminal emulator regards `*` as a wildcard.)

Our code should make it easy to implement further operations from `math.h` by

- adding an entry to `argtype`,
- adding a test to `getargtype`,
- add a new case to the `switch` statement in `main`.

Our use of `strcmp` makes it possible to use multi-character functions names like `sin` or `cos` out of the box.

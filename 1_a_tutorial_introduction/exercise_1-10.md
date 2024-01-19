# Exercise 1-10

> Write a program to copy its input to its output, replacing each tab by `\t`, each backspace by `\b`, and each backslash by `\\`.
> This makes tabs and backspaces visible in an unambiguous way.

---

We are using the not-yet introduced `else if` and `else` constructions to make the code more readable.
(Otherwise we would need nested `if`-statements.)
```c
#include <stdio.h>

int main(void)
{
	int c;

	c = 0; /* Dummy initial value. */
	while ((c = getchar()) != EOF) {
		if (c == '\t')
			printf("\\t");
		else if (c == '\b')
			printf("\\b");
		else if (c == '\\')
			printf("\\\\");
		else
			putchar(c);
	}
}
```

We can test this program with its own source code:
```text
#include <stdio.h>

int main(void)
{
\tint c;

\tc = 0; /* Dummy initial value. */
\twhile ((c = getchar()) != EOF) {
\t\tif (c == '\\t')
\t\t\tprintf("\\\\t");
\t\telse if (c == '\\b')
\t\t\tprintf("\\\\b");
\t\telse if (c == '\\\\')
\t\t\tprintf("\\\\\\\\");
\t\telse
\t\t\tputchar(c);
\t}
}
```

# Exercise 1-10

> Write a program to copy its input to its output, replacing each tab by `\t`, each backspace by `\b`, and each backslash by `\\`.
> This makes tabs and backspaces visible in an unambiguous way.



The code is somewhat ugly since we only have `if` (no `else` and no `switch`):
```c
#include <stdio.h>

int main(void)
{
	int c;

	c = 0;
	while ((c = getchar()) != EOF) {
		if (c == '\t')
			printf("\\t");
		if (c != '\t') {
			if (c == '\b')
				printf("\\b");
			if (c != '\b') {
				if (c == '\\')
					printf("\\\\");
				if (c != '\\')
					putchar(c);
			}
		}
	}
}
```

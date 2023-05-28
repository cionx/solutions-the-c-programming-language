# Exercise 1-8

> Write a program to count blanks, tabs, and newlines.



We simply extend the code from subsection 1.5.3:
```c
#include <stdio.h>

int main(void)
{
	int count, c;

	count = 0;
	while ((c = getchar()) != EOF) {
		if (c == ' ')
			++count;
		if (c == '\t')
			++count;
		if (c == '\n')
			++count;
	}

	printf("%d\n", count);
}
```
It would be better to use only one `if` with the condition `c == ' ' || c == '\t' || c == '\n'`, but we haven’t met the logical conjunction operator `||` yet.

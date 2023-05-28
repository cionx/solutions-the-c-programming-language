# Exercise 1-9

> Write a program to copy its input to its output, replacing each string of one or more blanks by a single blank.



We start with the program from subsection 1.5.1 that simply copies its input to its output.
But whenever we encounter a blank, we gobble up all following spaces;
we only stop once we have arrived at a non-blank character.
Before returning to the main loop we have to output this non-blank character, because otherwise it would get overwritten by the next call to `getchar` before it had the chance of getting to the output.
```c
#include <stdio.h>

int main(void)
{
	int c;

	c = 0;
	
	while ((c = getchar()) != EOF) {
		putchar(c);
		if (c == ' ') {
			while ((c = getchar()) == ' ')
				;
			putchar(c);
		}
	}
}
```

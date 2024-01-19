# Exercise 1-8

> Write a program to count blanks, tabs, and newlines.

---

We simply extend the code from subsection 1.5.3 to handle three counters at once:
```c
#include <stdio.h>

int main(void)
{
	int c;
	long count_blank, count_tab, count_newline;

	count_blank = count_tab = count_newline = 0;
	while ((c = getchar()) != EOF) {
		if (c == ' ')
			++count_blank;
		if (c == '\t')
			++count_tab;
		if (c == '\n')
			++count_newline;
	}

	printf("Blanks: %ld\n", count_blank);
	printf("Tabs:   %ld\n", count_tab);
	printf("Lines:  %ld\n", count_newline);
}
```

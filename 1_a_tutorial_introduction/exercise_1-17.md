# Exercise 1-17

> Write a program to print all input lines that are longer than 80 characters.

---

We can adjust the code from the longest-line program, printing only those lines that have at least 81 characters (including the trailing newline character).
```c
#include <stdio.h>

#define MAXLINE   1000 /* Maximum input line size. */
#define MINLENGTH 81   /* Minimal allowed line length. */

int getaline(char line[], int maxline);

/* Print input lines longer than MINLENGTH characters. */
int main(void)
{
	int len;            /* Current line length. */
	char line[MAXLINE]; /* Current input line. */

	while ((len = getaline(line, MAXLINE)) > 0)
		if (len >= MINLENGTH)
			printf("%s", line);

	return 0;
}

/* getaline: read a line into s, return length. */
int getaline(char s[], int lim)
{
	int c, i;

	c = 0;
	for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; ++i)
		s[i] = (char) c;
	if (c == '\n') {
		s[i] = (char) c;
		++i;
	}
	s[i] = '\0';
	return i;
}
```

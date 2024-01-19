# Exercise 1-18

> Write a program to remove trailing blanks and tabs from each line of input, and to delete entirely blank lines.

---

We use an auxiliary function `trim` that removes all trailing whitespace from a string.
This function starts at the end of the string and replaces every kind of white space by `\0`.
It stops when it encounters a non-whitespace character or when it has gone through the entire string.
Afterwards, we have two cases to consider:

- If we went through the entire string, then this means that we were dealing with a blank string.
  In this case we do nothing else, which leaves the string empty.
  (This takes care of blank lines.)

- Otherwise, we need to add back a newline character if the original string ended in one.

This strategy leads to the following code:
```c
#include <stdio.h>

#define MAXLINE 1000 /* Maximum input line size. */

int getaline(char line[], int maxline);
void trim(char s[], int length);

/* Removes all trailing whitespace, as well as blank lines. */
int main(void)
{
	int len;            /* Current line length. */
	char line[MAXLINE]; /* Current input line. */

	while ((len = getaline(line, MAXLINE)) > 0) {
		trim(line, len);
		printf("%s", line);
	}

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

/* trim: remove trailing whitespace from a string. */
void trim(char s[], int length)
{
	int i;
	int c;

	c = s[length - 1]; // Remember the last character for later.

	i = length - 1;
	while (i >= 0 && (s[i] == ' ' || s[i] == '\t' || s[i] == '\n')) {
		s[i] = '\0';
		--i;
	}
	if (i >= 0 && c == '\n')
		s[i + 1] = '\n';
}
```

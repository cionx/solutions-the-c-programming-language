# Exercise 1-21

> Write a program `entab` that replaces strings of blanks by the minimum number of tabs and blanks to achieve the same spacing.
> Use the same tab stops as for `detab`.
> When either a tab or a single blank would suffice to reach a tab stop, which should be given preference?

---

We write a function `entab` that replaces leading blanks by leading tabs and blanks.
```c
/* Replaces leading blanks by the equivalent amount of tabs and blanks.
 * The tab length must be positive. */
void entab(char s[], int tablen)
{
	/* Index i for reading, j for writing. */
	int i = 0, j = 0;

	int blankcount = 0;
	/* Count the number of leading blanks. */
	for (; s[i] == ' '; ++i)
		++blankcount;
	/* Add as many tabs as possible. */
	for (; blankcount >= tablen; blankcount -= tablen)
		s[j++] = '\t';
	/* Add remaining spaces. */
	for (; blankcount > 0; --blankcount)
		s[j++] = ' ';
	/* Move the rest of the string at the correct position. */
	while ((s[j++] = s[i++]) != '\0')
		;
}
```

We set the default tab length via a macro.
```c
#include <stdio.h>

#define MAXLEN 100000
#define TABLEN 4

void entab(char s[], int tablen);
int getaline(char line[], int lim);

int main(void)
{
	char line[MAXLEN];

	while (getaline(line, MAXLEN) > 0) {
		entab(line, TABLEN);
		printf("%s", line);
	}

	return 0;
}
```

The function `getaline` is as usual:
```c
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

We tested our function with the following text and various values for `TABLEN`.
```text
0 leading spaces
 1 leading spaces
  2 leading spaces
   3 leading spaces
    4 leading spaces
     5 leading spaces
      6 leading spaces
       7 leading spaces
        8 leading spaces
         9 leading spaces
          10 leading spaces
           11 leading spaces
            12 leading spaces
```
We got the correct result in each case.

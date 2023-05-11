# Exercise 1-21

> Write a program `entab` that replaces strings of blanks by the minimum number of tabs and blanks to achieve the same spacing.
> Use the same tab stops as for `detab`.
> When either a tab or a single blank would suffice to reach a tab stop, which should be given preference?

We have the following cases to consider.

1. The tabwidth is at least 2.

2. The tabwidth is 1.

3. The tabwidth is 0.

In the third case we need to delete all tabs.

In the first case we need to use as many tabs as possible, and fill in the missing space with blanks.
To determine the location of the blanks, we will follow the golden rule of blanks and tabs:

- Only place tabs as the beginning of a line.
  (Tabs for indentation, blanks for alignment.)

Following this rule, we will place the required blanks after all used tabs.

The second case is the problematic one.
Following the above rule, we will first use tabs and then blanks.
But there doesn’t seem to be a good way for deciding where to switch.
For consistency, we will use only tabs:
this agrees with the “as many tabs as possible” behaviour from the first, generic case.

If, for whatever reason, the input consists of multiple lines of whitespace, then we’ll work through each line on its own.

```c
#include <stdio.h>

#define MAXLEN      100000

int tabsize;

void set_tabsize(int size);
void retab(char s[]);
void rm_tabs(char s[]);
void entab(char s[]);
int getaline(char line[], int lim);

int main(void)
{
	char line[MAXLEN];

	set_tabsize(4);

	while (getaline(line, MAXLEN) > 0) {
		retab(line);
		printf("%s", line);
	}

	return 0;
}

void set_tabsize(int size)
{
	extern int tabsize;
	tabsize = size;
}

void retab(char s[]) {
	extern int tabsize;

	if (tabsize == 0)
		rm_tabs(s);
	else
		entab(s);
}

/* Removes tabs from a string. */
void rm_tabs(char s[])
{
	int j;

	j = 0;
	for (int i = 0; s[i] != '\0'; ++i)
		if (s[i] != '\t') {
			s[j] = s[i];
			++j;
		}
	s[j] = '\0';
}

/* Replaces whitespace by the equivalent amount of tabs and spaces.
   The input is assumed to consist only of whitespace, and to not be
   longer than a single line. */
void entab(char s[])
{
	extern int tabsize;
	int spaces;
	int i, j;

	spaces = 0;
	for (i = 0; s[i] != '\0'; ++i) {
		if (s[i] == ' ') {
			++spaces;
		}
		else if (s[i] == '\t') {
			spaces = spaces + tabsize - (spaces % tabsize);
		}
	}
	j = 0;
	while (spaces >= tabsize) {
		s[j] = '\t';
		++j;
		spaces = spaces - tabsize;
	}
	while (spaces > 0) {
		s[j] = ' ';
		++j;
		--spaces;
	}
	if (i > 0 && s[i - 1] == '\n') {
		s[j] = '\n';
		++j;
	}
	s[j] = '\0';
}

int getaline(char s[], int lim)
{
	int c, i;
	
	c = 0;
	for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; ++i)
		s[i] = c;
	if (c == '\n') {
		s[i] = c;
		++i;
	}
	s[i] = '\0';
	return i;
}
```

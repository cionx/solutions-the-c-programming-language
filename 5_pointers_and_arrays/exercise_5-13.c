#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h> /* for atoi */

#define MAXLINES 100000

bool isnumber(char *s);
int readlines(char *lineptr[], int maxlines);

int main(int argc, char *argv[])
{
	/* Determine the number of lines to be printed. */
	int n = 10;
	while (--argc > 0) {
		char *argument = *++argv;
		if (argument[0] != '-') {
			printf("tail: Unknown argument %s\n", argument);
			return 1;
		}
		if (!isnumber(argument + 1)) {
			printf("tail: Unknown flag %s\n", argument);
			return 1;
		}
		n = atoi(argument + 1);
	}

	/* Reading the lines. */
	char *lineptr[MAXLINES];
	int linetotal = readlines(lineptr, MAXLINES);

	/* Printing the lines. */
	int start = (n >= linetotal) ? 0 : linetotal - n;
	for (int i = start; i < linetotal; ++i)
		printf("%s\n", lineptr[i]);

	return 0;
}

bool isnumber(char *s)
{
	while (isdigit(*s))
		++s;
	return (*s == '\0');
}

/* READLINES */

#include <string.h>

#define MAXLEN 1000 /* max length of any input line */

int getaline(char *, int);
char *alloc(int);

/* readlines: read input lines */
int readlines(char *lineptr[], int maxlines)
{
	int len, nlines;
	char *p, line[MAXLEN];
	nlines = 0;
	while ((len = getaline(line, MAXLEN)) > 0)
		if (nlines >= maxlines || (p = alloc(len)) == NULL)
			return -1;
		else {
			line[len - 1] = '\0'; /* delete newline */
			strcpy(p, line);
			lineptr[nlines++] = p;
		}
	return nlines;
}

/* GETALINE */

int getaline(char s[], int lim)
{
	int c, i;
	for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; ++i)
		s[i] = (char) c;
	if (c == '\n') {
		s[i] = (char) c;
		++i;
	}
	s[i] = '\0';
	return i;
}

/* ALLOC */

#define ALLOCSIZE 1000000 /* size of available space */

static char allocbuf[ALLOCSIZE]; /* storage for alloc */
static char *allocp = allocbuf;  /* next free position */

char *alloc(int n) /* return pointer to n characters */
{
	if (allocbuf + ALLOCSIZE - allocp >= n) { /* it fits */
		allocp += n;
		return allocp - n; /* old p */
	}
	else /* not enough room */
		return 0;
}

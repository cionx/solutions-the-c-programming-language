# Exercise 5-15

> Add the option `-f` to fold upper and lower case together, so that case distinctions are not made during sorting;
> for example, `a` and `A` compare equal.

---

We replace the boolean `numeric` by an enum `sortmode` that encompasses the three values `string`, `numeric`, `folded`.
```c
enum sortmode { string, numeric, folded };

/* sort input lines */
int main(int argc, char *argv[])
{
	enum sortmode mode = string; /* default sort mode */
	bool reversed = false;       /* true if reverse sort */

	/* Read the flags. */
	while (--argc > 0) {
		char *arg = *++argv;
		if (arg[0] != '-') {
			printf("Unknown option: %s\n", arg);
			return 1;
		}
		for (int i = 1; arg[i] != '\0'; ++i) {
			switch (arg[i]) {
				case 'n':
					mode = numeric;
					break;
				case 'f':
					mode = folded;
					break;
				case 'r':
					reversed = true;
					break;
				default:
					printf("Unknown flag: %c\n", arg[i]);
					return 1;
			}
		}
	}
```

We write a custom comparison function for each mode:
```c
/* COMPARISON FUNCTIONS */

#include <ctype.h>
#include <stdlib.h>

/* stringcmp: a wrapper around strcmp */
int stringcmp(const void *vs1, const void *vs2)
{
	const char *s1 = (const char *) vs1;
	const char *s2 = (const char *) vs2;
	return strcmp(s1, s2);
}

/* numcmp: compare s1 and s2 numerically */
int numcmp(const void *vs1, const void *vs2)
{
	const char *s1 = (const char *) vs1;
	const char *s2 = (const char *) vs2;
	double v1, v2;
	v1 = atof(s1);
	v2 = atof(s2);
	if (v1 < v2)
		return -1;
	else if (v1 > v2)
		return 1;
	else
		return 0;
}

/* foldcmp: compare s and t without case distinction */
int foldcmp(const void *vs, const void *vt)
{
	const char *s = (const char *) vs;
	const char *t = (const char *) vt;
	for (; tolower(*s) == tolower(*t); ++s, ++t)
		if (*s == '\0')
			return 0;
	return tolower(*s) - tolower(*t);
}
```
The code for `foldcmp` is a variation of `strcmp` from page 106.
The function `tolower` comes from `ctype.h`:
it makes uppercase letters lowercase, and leaves all other characters the same.

Back in `main` we choose the comparison function depending on the mode:
```c
	/* The actual sorting. */
	int nlines; /* number of input lines read */
	if ((nlines = readlines(lineptr, MAXLINES)) >= 0) {
		int (*cmpfun)(const void *, const void *);
		switch (mode) {
			case string:
				cmpfun = stringcmp;
				break;
			case numeric:
				cmpfun = numcmp;
				break;
			case folded:
				cmpfun = foldcmp;
				break;
		}
```
We then sort the lines with respect to this comparison function, and reverse the result if so required:
```c
		quicksort((void **) lineptr, 0, nlines - 1, cmpfun);
		if (reversed) /* Reverse the result if requested. */
			reverse((void **) lineptr, 0, nlines - 1);
		writelines(lineptr, nlines);
		return 0;
	}
	else {
		printf("input too big to sort\n");
		return 1;
	}
}
```

## Entire code

The entire code is as follows:
```c
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#define MAXLINES 5000 /* max #lines to be sorted */

static char *lineptr[MAXLINES]; /* pointers to text lines */

int readlines(char *lineptr[], int nlines);
void writelines(char *lineptr[], int nlines);
void quicksort(void *lineptr[], int left, int right,
               int (*comp)(const void *, const void *));
int stringcmp(const void *, const void *);
int numcmp(const void *, const void *);
int foldcmp(const void *, const void *);
void reverse(void *v[], int i, int j);

enum sortmode { string, numeric, folded };

/* sort input lines */
int main(int argc, char *argv[])
{
	enum sortmode mode = string; /* default sort mode */
	bool reversed = false;       /* true if reverse sort */

	/* Read the flags. */
	while (--argc > 0) {
		char *arg = *++argv;
		if (arg[0] != '-') {
			printf("Unknown option: %s\n", arg);
			return 1;
		}
		for (int i = 1; arg[i] != '\0'; ++i) {
			switch (arg[i]) {
				case 'n':
					mode = numeric;
					break;
				case 'f':
					mode = folded;
					break;
				case 'r':
					reversed = true;
					break;
				default:
					printf("Unknown flag: %c\n", arg[i]);
					return 1;
			}
		}
	}

	/* The actual sorting. */
	int nlines; /* number of input lines read */
	if ((nlines = readlines(lineptr, MAXLINES)) >= 0) {
		int (*cmpfun)(const void *, const void *);
		switch (mode) {
			case string:
				cmpfun = stringcmp;
				break;
			case numeric:
				cmpfun = numcmp;
				break;
			case folded:
				cmpfun = foldcmp;
				break;
		}
		quicksort((void **) lineptr, 0, nlines - 1, cmpfun);
		if (reversed) /* Reverse the result if requested. */
			reverse((void **) lineptr, 0, nlines - 1);
		writelines(lineptr, nlines);
		return 0;
	}
	else {
		printf("input too big to sort\n");
		return 1;
	}
}

/* QUICKSORT */

void swap(void *v[], int i, int j);

/* qsort: sort v[left]...v[right] into increasing order */
void quicksort(void *v[], int left, int right,
               int (*comp)(const void *, const void *))
{
	int i, last;
	if (left >= right) /* do nothing if array contains */
		return;        /* fewer than two elements */
	swap(v, left, (left + right) / 2);
	last = left;
	for (i = left + 1; i <= right; i++)
		if ((*comp)(v[i], v[left]) < 0)
			swap(v, ++last, i);
	swap(v, left, last);
	quicksort(v, left, last - 1, comp);
	quicksort(v, last + 1, right, comp);
}

void swap(void *v[], int i, int j)
{
	void *tmp;
	tmp = v[i];
	v[i] = v[j];
	v[j] = tmp;
}

/* COMPARISON FUNCTIONS */

#include <ctype.h>
#include <stdlib.h>

/* stringcmp: a wrapper around strcmp */
int stringcmp(const void *vs1, const void *vs2)
{
	const char *s1 = (const char *) vs1;
	const char *s2 = (const char *) vs2;
	return strcmp(s1, s2);
}

/* numcmp: compare s1 and s2 numerically */
int numcmp(const void *vs1, const void *vs2)
{
	const char *s1 = (const char *) vs1;
	const char *s2 = (const char *) vs2;
	double v1, v2;
	v1 = atof(s1);
	v2 = atof(s2);
	if (v1 < v2)
		return -1;
	else if (v1 > v2)
		return 1;
	else
		return 0;
}

/* foldcmp: compare s and t without case distinction */
int foldcmp(const void *vs, const void *vt)
{
	const char *s = (const char *) vs;
	const char *t = (const char *) vt;
	for (; tolower(*s) == tolower(*t); ++s, ++t)
		if (*s == '\0')
			return 0;
	return tolower(*s) - tolower(*t);
}

/* REVERSE */

void reverse(void *v[], int i, int j)
{
	for (; i < j; ++i, --j)
		swap(v, i, j);
}

/* READLINES & WRITELINES */

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

/* writelines: write output lines */
void writelines(char *lineptr[], int nlines)
{
	int i;
	for (i = 0; i < nlines; i++)
		printf("%s\n", lineptr[i]);
}

/* ALLOC */

#define ALLOCSIZE 100000 /* size of available space */

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

/* GETALINE */

/* getaline: read a line into s, return length */
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
```

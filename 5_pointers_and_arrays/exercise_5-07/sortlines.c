/* MAIN */

#include <stdio.h>
#include <string.h>

#define MAXLINES 5000           /* maximum number of lines to be sorted */

static char *lineptr[MAXLINES]; /* pointers to text lines */

int readlines(char *lineptr[], int nlines);
void writelines(char *lineptr[], int nlines);

void qsort(char *lineptr[], int left, int right);

/* sort input lines */
int main(void)
{
	int nlines; /* number of input lines read */

	if ((nlines = readlines(lineptr, MAXLINES)) >= 0) {
		qsort(lineptr, 0, nlines - 1);
		writelines(lineptr, nlines);
		return 0;
	}
	else {
		printf("error: input too big to sort\n");
		return 1;
	}
}

/* READING AND WRITING OF LINES */

#define MAXLEN 1000 /* max length of any input line */

int getaline(char *s, int lim);
char *alloc(int size);

/* readlines: read input lines */
int readlines(char *lineptr[], int maxlines)
{
	int len, nlines;
	char *p, line[MAXLEN];

	nlines = 0;
	while ((len = getaline(line, MAXLEN)) > 0) {
		if (nlines >= maxlines || (p = alloc(len)) == NULL)
			return -1;
		else {
			line[len - 1] = '\0'; /* delete newline */
			strcpy(p, line);
			lineptr[nlines++] = p;
		}
	}
	return nlines;
}

/* writelines: write output lines */
void writelines(char *lineptr[], int nlines)
{
	for (int i = 0; i < nlines; ++i)
		printf("%s\n", lineptr[i]);
}

/* QSORT */

void swap(char *v[], int i, int j);

/* qsort: sort v[left]...v[right] into increasing order */
void qsort(char *v[], int left, int right)
{
	int last;

	if (left >= right) /* do nothing if array contains */
		return;        /* fewer than two elements */
	swap(v, left, left + (right - left) / 2);
	last = left;
	for (int i = left + 1; i <= right; ++i)
		if (strcmp(v[i], v[left]) < 0)
			swap(v, ++last, i);
	swap(v, left, last);
	qsort(v, left, last - 1);
	qsort(v, last + 1, right);
}

void swap(char *v[], int i, int j)
{
	char *temp;

	temp = v[i];
	v[i] = v[j];
	v[j] = temp;
}

/* GETALINE, from Section 1.9 */

/* getline: read a line into s, return length */
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

/* ALLOC, from Section 5.4 */

#define ALLOCSIZE 100000 /* size of available space */

static char allocbuf[ALLOCSIZE];
/* storage for alloc */
static char *allocp = allocbuf;

/* next free position */
char *alloc(int n) /* return pointer to n characters */
{
	if (allocbuf + ALLOCSIZE - allocp >= n) { /* it fits */
		allocp += n;
		return allocp - n;                    /* old p */
	}
	else
		/* not enough room */
		return 0;
}

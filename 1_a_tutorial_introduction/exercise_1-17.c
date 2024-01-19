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

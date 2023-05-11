
#include <stdio.h>

#define MAXLINE 1000 /* maximum input line size */

int getaline(char line[], int maxline);
int morelength(void);
void copy(char to[], char from[]);

/* print longest input line */
int main(void)
{
	int len;                /* current line length */
	int max;                /* maximal length seen so far */
	char line[MAXLINE];     /* current input line */
	char longest[MAXLINE];  /* longest line saved here */

	max = 0;
	while ((len = getaline(line, MAXLINE)) > 0) {
		if (len == MAXLINE - 1 && line[MAXLINE - 2] != '\n')
			len = len + morelength();
		if (len > max) {
			max = len;
			copy(longest, line);
		}
	}
	if (max > 0) /* there was a line */
		printf("Longest line: %d characters\n%s\n", max, longest);

	return 0;
}

/* counts additional length */
int morelength(void)
{
	int c;
	int counter;

	c = 0;
	counter = 0;
	while ((c = getchar()) != '\n' && c != EOF)
		++counter;

	return counter;
}

/* getaline: read a line into s, return length */
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

/* copy: copy 'from' into 'to'; assume to is big enough */
void copy(char to[], char from[])
{
	int i;
	
	i = 0;
	while ((to[i] = from[i]) != '\0')
		++i;
}

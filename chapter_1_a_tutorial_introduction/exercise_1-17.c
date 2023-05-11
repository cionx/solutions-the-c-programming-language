#include <stdio.h>

#define MAXLINE 1000 /* maximum input line size */

int getaline(char line[], int maxline);

/* print longest input line */
int main(void)
{
	int len;                /* current line length */
	char line[MAXLINE];     /* current input line */

	while ((len = getaline(line, MAXLINE)) > 0)
		if (len > 80)
			printf("%s", line);

	return 0;
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

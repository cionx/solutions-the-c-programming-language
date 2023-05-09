#include <stdio.h>

#define MAXLINE 1000 /* maximum input line size */

int getaline(char line[], int maxline);
void trim(char s[], int length);

/* removes all trailing whitespace, as well as blank lines */
int main(void)
{
	int len;                /* current line length */
	char line[MAXLINE];     /* current input line */

	while ((len = getaline(line, MAXLINE)) > 0) {
		trim(line, len);
		printf("%s", line);
	}
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

/* trim: remove trailing whitespace from a string */
void trim(char s[], int length)
{
	int i;
	int c;

	c = s[length - 1]; // remember the last character for later

	i = length - 1; //
	while (i >= 0 && (s[i] == ' ' || s[i] == '\t' || s[i] == '\n')) {
		s[i] = '\0';
		--i;
	}
	if (i >= 0 && c == '\n')
		s[i + 1] = '\n';
}

#include <stdio.h>

#define MAXLINE  1000
#define LENERROR -1
#define TABSIZE  4

int detab(char s[], int tabsize);
int getaline(char line[], int lim);

int main(void)
{
	char line[MAXLINE];
	int code = 0;

	while (getaline(line, MAXLINE) > 0) {
		if ((code = detab(line, TABSIZE)) < 0)
			return code;
		printf("%s", line);
	}

	return 0;
}

int detab(char line[], int tabsize)
{
	char result[MAXLINE];
	int j;      /* Position in `result` to write to. */
	int spaces; /* How many spaces a tab at the current position is worth. */

	j = 0;
	spaces = tabsize;
	for (int i = 0; i < MAXLINE && line[i] != '\0' && j < MAXLINE; ++i) {
		/* Either expand a tab character... */
		if (line[i] == '\t') {
			for (; spaces > 0 && j < MAXLINE; --spaces, ++j)
				result[j] = ' ';
		}
		/* ... or just copy the current character. */
		else {
			result[j] = line[i];
			--spaces;
			++j;
		}
		if (spaces == 0)
			spaces = tabsize;
	}

	/* Check if the result fits into MAXLINE. More explicitly, check if there is
	 * enough space left to add \0. */
	if (j >= MAXLINE) {
		printf("Error: Not enough space to expand with tabwidth %d:\n\"%s\"",
		       tabsize, line);
		return LENERROR;
	}
	result[j] = '\0';

	/* Finally, copy the result back into `line`, including the trailing \0. */
	for (int i = 0; i <= j; ++i) {
		line[i] = result[i];
	}

	/* Return the length of the detabed line. */
	return j;
}

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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLEN      100000
#define DFLT_TABLEN 4

void entab(char s[], int tablen);
int getaline(char line[], int lim);

int main(int argc, char *argv[])
{
	char line[MAXLEN];
	int tablen = DFLT_TABLEN;

	if (argc >= 2) {
		char *flag = argv[1];
		if (strcmp(flag, "-t") != 0) {
			printf("entab: unknown option %s\n", flag);
			return -1;
		}
		if (argc < 3) {
			printf("entab: missing tab length\n");
			return -1;
		}
		char *argument = argv[2];
		tablen = atoi(argument);
	}

	while (getaline(line, MAXLEN) > 0) {
		entab(line, tablen);
		printf("%s", line);
	}

	return 0;
}

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

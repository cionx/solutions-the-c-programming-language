#include <stdio.h>

#define MAXLEN 100000

#define TRUE    1
#define FALSE   0

int tabsize;
int columnsize;

void set_tabsize(int size);
void set_columnsize(int size);
int inword(char c);
int inws(char c);
int getaline(char line[], int limit);
int getword(char line[], char into[]);
int getws(char line[], char into[], int column);
void shorten(char s[], int n);

int main(void)
{
	extern int columnsize;

	char line[MAXLEN];
	char word[MAXLEN];
	char ws[MAXLEN];
	int wordlen;
	int wslen;

	int column;

	int emptyline;

	set_tabsize(4);
	set_columnsize(60);

	wslen = wordlen = 0;
	column = 0;
	emptyline = TRUE;
	while (getaline(line, MAXLEN) > 0) {
		column = 0;
		emptyline = TRUE;
		while (line[0] != '\0') {
			wslen = getws(line, ws, column);
			wordlen = getword(line, word);
			/* stay in the same line */
			if (columnsize - column >= wslen + wordlen) {
				printf("%s%s", ws, word);
				column = column + wslen + wordlen;
				emptyline = FALSE;
			}
			/* or enter a new line */
			else {
				if (emptyline == TRUE) {
					if (wslen > 0)
						printf("%s\n", ws);
					printf("%s", word);
				}
				else {
					printf("\n%s", word);
				}
				column = wordlen;
				emptyline = FALSE;
			}
		}
	}

	return 0;
}

/* set_columnsize: set the value of the variable columnsize */
void set_columnsize(int size)
{
	extern int columnsize;
	columnsize = size;
}

/* set_tabsize: set the value of the variable tabsize */
void set_tabsize(int size)
{
	extern int tabsize;
	tabsize = size;
}

/* inword: checks if we are dealing with non-whitespace */
int inword(char c)
{
	if (c != ' ' && c != '\t' && c != '\n' && c != '\0') {
		return TRUE;
	}
	else {
		return FALSE;
	}
}

/* inws: check if we are dealing with whitespace */
int inws(char c)
{
	if ((c == ' ' || c == '\t' || c == '\n') && c != '\0')
		return TRUE;
	else
		return FALSE;
}

/* getword: Reads a word from the beginning of a line into
   a provided string. Words are separated by whitespace.
   The found word is then removed from the beginning of the line.
   Returns the length of the found word. */
int getword(char line[], char into[])
{
	int i;

	for(i = 0; inword(line[i]); ++i) {
		into[i] = line[i];
	}
	into[i] = '\0';

	shorten(line, i);

	return i;
}

/* getws: Like getword, but reading off whitespace.
   Returns the length of the found whitespace, which requires
   correctly calculating the space that tabs take. This depends
   on which column of the original input we start off. */
int getws(char line[], char into[], int column)
{
	int i;
	int len;
	extern int tabsize;

	len = 0;
	for(i = 0; inws(line[i]); ++i) {
		into[i] = line[i];
		if (line[i] == ' ') {
			++len;
		}
		else if (line[i] == '\t') {
			len = len + tabsize - (column % 4);
		}
		/* if line[i] is \n then the length remains unchanged */
	}
	into[i] = '\0';

	shorten(line, i);

	return len;
}

/* shorten: Removes the first n characters from a string s. */
void shorten (char s[], int n)
{
	int i;

	for(i = 0; s[n + i] != '\0'; ++i)
		s[i] = s[n + i];
	s[i] = '\0';
}

/* getaline: Reads one line of input with getchar.
 * Returns the length of the line.                  */
int getaline(char line[], int limit)
{
	char c;
	int i;

	c = 0;
	for (i = 0; i < limit - 1 && (c = getchar()) != EOF && c != '\n'; ++i) {
		line[i] = c;
	}
	if (c == '\n') {
		line[i] = '\n';
		++i;
	}
	line[i] = '\0';
	return i;
}

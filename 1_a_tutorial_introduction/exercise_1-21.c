#include <stdio.h>

#define MAXLEN      100000

int tabsize;

void set_tabsize(int size);
void retab(char s[]);
void rm_tabs(char s[]);
void entab(char s[]);
int getaline(char line[], int lim);

int main(void)
{
	char line[MAXLEN];

	set_tabsize(4);

	while (getaline(line, MAXLEN) > 0) {
		retab(line);
		printf("%s", line);
	}

	return 0;
}

void set_tabsize(int size)
{
	extern int tabsize;
	tabsize = size;
}

void retab(char s[]) {
	extern int tabsize;

	if (tabsize == 0)
		rm_tabs(s);
	else
		entab(s);
}

/* Removes tabs from a string. */
void rm_tabs(char s[])
{
	int j;

	j = 0;
	for (int i = 0; s[i] != '\0'; ++i)
		if (s[i] != '\t') {
			s[j] = s[i];
			++j;
		}
	s[j] = '\0';
}

/* Replaces whitespace by the equivalent amount of tabs and spaces.
   The input is assumed to consist only of whitespace, and to not be
   longer than a single line. */
void entab(char s[])
{
	extern int tabsize;
	int spaces;
	int i, j;

	spaces = 0;
	for (i = 0; s[i] != '\0'; ++i) {
		if (s[i] == ' ') {
			++spaces;
		}
		else if (s[i] == '\t') {
			spaces = spaces + tabsize - (spaces % tabsize);
		}
	}
	j = 0;
	while (spaces >= tabsize) {
		s[j] = '\t';
		++j;
		spaces = spaces - tabsize;
	}
	while (spaces > 0) {
		s[j] = ' ';
		++j;
		--spaces;
	}
	if (i > 0 && s[i - 1] == '\n') {
		s[j] = '\n';
		++j;
	}
	s[j] = '\0';
}

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

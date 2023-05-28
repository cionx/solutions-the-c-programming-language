#include <stdio.h>

#define MAXLEN      100000
#define LENERROR    -1

int tabsize;

void set_tabsize(int size);
int replace_tabs(char s[], int max_len);
int getaline(char line[], int lim);

/* Main code */

int main(void)
{
	char line[MAXLEN];

	set_tabsize(4);

	while (getaline(line, MAXLEN) > 0) {
		replace_tabs(line, MAXLEN);
		printf("%s", line);
	}

	return 0;
}

void set_tabsize(int size)
{
	extern int tabsize;
	tabsize = size;
}

int replace_tabs(char s[], int max_len)
{
	int t[max_len];
	int j;
	int spaces;

	j = 0;
	spaces = tabsize;
	for (int i = 0; i < max_len && s[i] != '\0' && j < max_len; ++i) {
		if (s[i] == '\t') {
			for(; spaces > 0; --spaces) {
				t[j] = ' ';
				++j;
			}
			spaces = tabsize;
		}
		else {
			t[j] = s[i];
			--spaces;
			if (spaces == 0)
				spaces = tabsize;
			++j;
		}
	}

	if (j >= max_len) {
		printf("Error: Not enough space to expand with tabwidth %d:\n%s", tabsize, s);
		return LENERROR;
	}
	t[j] = '\0';

	for (int i = 0; i <= j; ++i) {
		s[i] = t[i];
	}

	return j;
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

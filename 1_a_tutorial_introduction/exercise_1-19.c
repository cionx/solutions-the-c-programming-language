#include <stdio.h>

#define MAXLINE 100000

void reverse(char s[]);
void reverse_line(char line[], int length);
int getaline(char s[], int lim);

int main(void)
{
	int len;
	char line[MAXLINE];

	while ((len = getaline(line, MAXLINE)) > 0) {
		reverse_line(line, len);
		printf("%s", line);
	}

	return 0;
}

void reverse_line(char line[], int length)
{
	if (line[length - 1] == '\n') {
		line[length - 1] = '\0';
		reverse(line);
		line[length - 1] = '\n';
	}
	else
		reverse(line);
}

void reverse(char s[])
{
	int last_index;

	last_index = 0;
	while (s[last_index] != '\0')
		++last_index;
	--last_index;

	for (int i = 0; i < last_index - i; ++i) {
		char tmp;
		tmp = s[i];
		s[i] = s[last_index - i];
		s[last_index - i] = tmp;
	}
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

#include <stdio.h>

#define MAXLINE 10000

void escape(char target[], const char source[]);
void unescape(char target[], const char source[]);
int getaline(char line[], int limit);

void escape(char target[], const char source[])
{
	int to = 0;
	for (int from = 0; source[from] != '\0'; ++from)
		switch (source[from]) {
			case '\t':
				target[to++] = '\\';
				target[to++] = 't';
				break;
			case '\n':
				target[to++] = '\\';
				target[to++] = 'n';
				break;
			case '\\':
				target[to++] = '\\';
				target[to++] = '\\';
				break;
			default:
				target[to++] = source[from];
				break;
		}
	target[to] = '\0';
}

void unescape(char target[], const char source[])
{
	int to = 0;
	for (int from = 0; source[from] != '\0'; ++from) {
		if (source[from] == '\\') {
			switch (source[from + 1]) {
				case 't':
					target[to++] = '\t';
					++from;
					break;
				case 'n':
					target[to++] = '\n';
					++from;
					break;
				case '\\':
					target[to++] = '\\';
					++from;
					break;
				default:
					target[to++] = '\\';
			}
		}
		else {
			target[to++] = source[from];
		}
	}
	target[to] = '\0';
}

int getaline(char line[], int limit)
{
	int c, i;

	c = 0;
	for (i = 0; i < limit - 1 && (c = getchar()) != EOF && c != '\n'; ++i) {
		line[i] = (char) c;
	}
	if (c == '\n') {
		line[i] = '\n';
		++i;
	}
	line[i] = '\0';
	return i;
}

int main(void)
{
	char line[MAXLINE];
	char escline[MAXLINE];
	while (getaline(line, MAXLINE) > 0) {
		escape(escline, line);
		printf("%s", escline);
		/* For testing
		unescape(line, escline);
		printf("%s", line); */
	}

	return 0;
}

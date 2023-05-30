#include <stdio.h>

#define MAXLINE 10000

void escape(char target[], const char source[]);
void unescape(char target[], const char source[]);
int getaline(char line[], int limit);

void escape(char target[], const char source[])
{
	int j = 0;
	for (int i = 0; source[i] != '\0'; ++i)
		switch (source[i]) {
			case '\t':
				target[j++] = '\\';
				target[j++] = 't';
				break;
			case '\n':
				target[j++] = '\\';
				target[j++] = 'n';
				break;
			case '\\':
				target[j++] = '\\';
				target[j++] = '\\';
				break;
			default:
				target[j++] = source[i];
				break;
		}
	target[j] = '\0';
}

void unescape(char target[], const char source[])
{
	int j = 0;
	for (int i = 0; source[i] != '\0'; ++i) {
		if (source[i] == '\\') {
			switch (source[i + 1]) {
				case 't':
					target[j++] = '\t';
					++i;
					break;
				case 'n':
					target[j++] = '\n';
					++i;
					break;
				case '\\':
					target[j++] = '\\';
					++i;
					break;
				default:
					target[j++] = '\\';
			}
		}
		else {
			target[j++] = source[i];
		}
	}
	target[j] = '\0';
}

int getaline(char line[], int limit)
{
	char c;
	int i;

	c = 0;
	for (i = 0; i < limit - 1 && (c = (char) getchar()) != EOF && c != '\n';
	     ++i) {
		line[i] = c;
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
		/* printf("%s", escline); */
		unescape(line, escline);
		printf("%s", line);
	}

	return 0;
}

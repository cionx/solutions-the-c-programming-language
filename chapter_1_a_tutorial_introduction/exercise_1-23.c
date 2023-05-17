#include <stdio.h>

#define NORMAL          0
#define COMMENT_MULTI   1
#define COMMENT_SINGLE  2
#define STRING          3
#define CHARACTER       4

#define MAXLEN          100000



int getaline(char line[], int limit);
void crawler_normal(char line[], int state_index[]);
void crawler_comment_multiline(char line[], int state_index[]);
void crawler_comment_singleline(char line[], int state_index[]);
void crawler_string(char line[], int state_index[]);
void crawler_character(char line[], int state_index[]);



int main(void)
{
	char line[MAXLEN];
	int state[2]; /* first entry is the current mode,
	                 second entry the current position in the line */

	state[0] = NORMAL;
	while (getaline(line, MAXLEN) > 0) {
		state[1] = 0;
		while (line[state[1]] != '\0') {
			crawler_normal(line, state);
			crawler_comment_multiline(line, state);
			crawler_comment_singleline(line, state);
			crawler_string(line, state);
			crawler_character(line, state);
		}
	}

	return 0;
}



void crawler_normal(char line[], int state[])
{
	char c;
	int mode;
	int i;
	mode = state[0];
	i = state[1];

	while (mode == NORMAL && (c = line[i]) != '\0') {
		if (c == '/') {
			if (line[i + 1] == '*') {
				mode = COMMENT_MULTI;
				++i;
			}
			else if (line[i + 1] == '/') {
				mode = COMMENT_SINGLE;
				++i;
			}
			else
				putchar('/');
		}
		else if (c == '\"') {
			putchar('\"');
			mode = STRING;
		}
		else if (c == '\'') {
			putchar('\'');
			mode = CHARACTER;
		}
		else
			putchar(c);
		++i;
	}

	state[0] = mode;
	state[1] = i;
}



void crawler_comment_multiline(char line[], int state[])
{
	int mode;
	int i;
	mode = state[0];
	i = state[1];

	while (mode == COMMENT_MULTI && line[i] != '\0') {
		if (line[i] == '*' && line[i + 1] == '/') {
			mode = NORMAL;
			++i;
		}
		++i;
	}

	state[0] = mode;
	state[1] = i;
}



void crawler_comment_singleline(char line[], int state[])
{
	int mode;
	int i;
	mode = state[0];
	i = state[1];

	if (mode == COMMENT_SINGLE) { // This is for testing.
		while (line[i] != '\0')
			++i;
		putchar('\n');
		mode = NORMAL;
	}

	state[0] = mode;
	state[1] = i;
}



void crawler_string(char line[], int state[])
{
	int mode;
	int i;
	mode = state[0];
	i = state[1];

	while (mode == STRING && line[i] != '\0') {
		putchar(line[i]);
		if (line[i] == '\"') {
			int backslashes;
			backslashes = 0;
			for (int j = i - 1; j > 0 && line[i] == '\\'; --j)
				++backslashes;
			if (backslashes % 2 == 0)
				mode = NORMAL;
		}
		++i;
	}

	state[0] = mode;
	state[1] = i;
}



void crawler_character(char line[], int state[])
{
	int mode;
	int i;
	mode = state[0];
	i = state[1];

	while (mode == CHARACTER && line[i] != '\0') {
		putchar(line[i]);
		if (line[i] == '\'') {
			int backslashes;
			backslashes = 0;
			for (int j = i - 1; j > 0 && line[i] == '\\'; --j)
				++backslashes;
			if (backslashes % 2 == 0)
				mode = NORMAL;
		}
		++i;
	}

	state[0] = mode;
	state[1] = i;
}



/* getaline: Reads one line of input with getchar.
   Returns the length of the line. */
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

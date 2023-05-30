# Exercise 3-2

> Write a function `escape(s, t)` that converts characters like newline and tab into visible escape sequences like `\n` and `\t` as it copies the string `t` to `s`.
> Use a `switch`.
> Write a function for the other direction as well, converting escape sequences into the real characters.


Apart from the whitespace characters `\t` and `\n`, we will also escape backslashes; it is otherwise not possible to distinguish the single character `'\t'` from the two-character string `"\\t"` in the output.
This then makes it impossible to retrieve the original text via `unescape`.
```c
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
```
The inverse function, `unescape`, is then as follows:
```
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
```

As an example, applying `escape` line-wise to its own source code results in the following string:
```c
void escape(char target[], const char source[])\n{\n\tint j = 0;\n\tfor (int i = 0; source[i] != '\\0'; ++i)\n\t\tswitch (source[i]) {\n\t\t\tcase '\\t':\n\t\t\t\ttarget[j++] = '\\\\';\n\t\t\t\ttarget[j++] = 't';\n\t\t\t\tbreak;\n\t\t\tcase '\\n':\n\t\t\t\ttarget[j++] = '\\\\';\n\t\t\t\ttarget[j++] = 'n';\n\t\t\t\tbreak;\n\t\t\tcase '\\\\':\n\t\t\t\ttarget[j++] = '\\\\';\n\t\t\t\ttarget[j++] = '\\\\';\n\t\t\t\tbreak;\n\t\t\tdefault:\n\t\t\t\ttarget[j++] = source[i];\n\t\t\t\tbreak;\n\t\t}\n\ttarget[j] = '\\0';\n}\n
```
Applying `unescape` to this string gives back the source code.

If we hadn’t also escaped backslashes, then the output would look as follows instead:
```text
void escape(char target[], const char source[])
{
	int j = 0;
	for (int i = 0; source[i] != '\0'; ++i)
		switch (source[i]) {
			case '	':
				target[j++] = '\\';
				target[j++] = 't';
				break;
			case '
':
				target[j++] = '\\';
				target[j++] = 'n';
				break;
			default:
				target[j++] = source[i];
				break;
		}
	target[j] = '\0';
}
```

We have used the function `getaline` from last chapter to do the above test:
```c
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
```

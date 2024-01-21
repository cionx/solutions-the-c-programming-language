# Exercise 3-2

> Write a function `escape(s, t)` that converts characters like newline and tab into visible escape sequences like `\n` and `\t` as it copies the string `t` to `s`.
> Use a `switch`.
> Write a function for the other direction as well, converting escape sequences into the real characters.

---

Apart from the whitespace characters `\t` and `\n`, we will also escape backslashes; it is otherwise not possible to distinguish the single character `'\t'` from the two-character string `"\\t"` in the output.
This would then make it impossible to retrieve the original text via `unescape`.
```c
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
```
The inverse function, `unescape`, is then as follows:
```c
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
```

As an example, applying `escape` to its own source code results in the following string:
```c
void escape(char target[], const char source[])\n{\n\tint to = 0;\n\tfor (int from = 0; source[from] != '\\0'; ++from)\n\t\tswitch (source[from]) {\n\t\t\tcase '\\t':\n\t\t\t\ttarget[to++] = '\\\\';\n\t\t\t\ttarget[to++] = 't';\n\t\t\t\tbreak;\n\t\t\tcase '\\n':\n\t\t\t\ttarget[to++] = '\\\\';\n\t\t\t\ttarget[to++] = 'n';\n\t\t\t\tbreak;\n\t\t\tcase '\\\\':\n\t\t\t\ttarget[to++] = '\\\\';\n\t\t\t\ttarget[to++] = '\\\\';\n\t\t\t\tbreak;\n\t\t\tdefault:\n\t\t\t\ttarget[to++] = source[from];\n\t\t\t\tbreak;\n\t\t}\n\ttarget[to] = '\\0';\n}\n
```
Applying `unescape` to this string then gives back the original source code.



## The complete source code

We have used the function `getaline` from last chapter to do the above test:
```c
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
```

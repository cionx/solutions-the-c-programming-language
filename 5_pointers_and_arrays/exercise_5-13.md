# Exercise 5-13

> Write the program `tail`, which prints the last `n` lines of its input.
> By default, `n` is 10, let us say, but it can be changed by an optional argument,
> so that
> ```sh
> tail -n
> ```
> prints the last `n` lines.
> The program should behave rationally no matter how unreasonable the input or the value of `n`.
> Write the program so it makes the best use of available storage;
> lines should be stored as in the sorting program of Section 5.6, not in a two-dimensional array of fixed size.

---

We chose a naive implementation:
read all lines with `readlines`, and then output the last `n` lines.

(It would be better to only remember the last `n` lines at any point in time, and then output all remembered lines at the end.
But we’d need a suitable data structure in which to save the lines, and we don’t know a good solution with what we know so far.)

We get the following `main` function:
```c
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h> /* for atoi */

#define MAXLINES 100000

bool isnumber(char *s);
int readlines(char *lineptr[], int maxlines);

int main(int argc, char *argv[])
{
	/* Determine the number of lines to be printed. */
	int n = 10;
	while (--argc > 0) {
		char *argument = *++argv;
		if (argument[0] != '-') {
			printf("Unknown argument %s\n", argument);
			return 1;
		}
		if (!isnumber(argument + 1)) {
			printf("Unknown flag %s\n", argument);
			return 1;
		}
		n = atoi(argument + 1);
	}

	/* Reading the lines. */
	char *lineptr[MAXLINES];
	int linetotal = readlines(lineptr, MAXLINES);

	/* Printing the lines. */
	int start = (n >= linetotal) ? 0 : linetotal - n;
	for (int i = start; i < linetotal; ++i)
		printf("%s\n", lineptr[i]);

	return 0;
}

bool isnumber(char *s)
{
	while (isdigit(*s))
		++s;
	return (*s == '\0');
}
```

We tested our program as follows:
```sh
$ cat exercise_5-13.c | ./a.out -5
```
The output seemed to be correct all values of `n` that we tested.

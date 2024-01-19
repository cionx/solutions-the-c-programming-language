# Exercise 1-16

> Revise the main routine of the longest-line program so it will correctly print the length of arbitrary long input lines, and as much as possible of the text.

---

For lines that are shorter than `MAXLEN - 1` we don’t need to change anything.
For larger lines we have the problem that `getline` (which we renamed to `getaline` to avoid conflicts with `stdio`) doesn’t read the entire line.
But we need to know how many characters are still left in such overly long lines.

To this end we introduce an auxiliary function `morelength` that reads off the remaining number of characters in the current line:
```c
/* Counts additional length. */
int morelength(void)
{
	int c;
	int counter;

	c = 0; /* Dummy initial value. */
	counter = 0;
	while ((c = getchar()) != '\n' && c != EOF)
		++counter;
	if (c == '\n')
		++counter;

	return counter;
}
```
This function simply counts how many more characters there are until the next line break or `EOF` (even though the `EOF` case should never occur).
We can detect if `getaline` left characters in the current line by checking if the length returned by `getaline` is `MAXLEN - 1` (so that `getaline` used up the entire space of `line`) and the second to last character is not a newline character (the last character is always `\0`).

This approach leads to the following modified main function:
```c
/* Print longest input line. */
int main(void)
{
	int len;               /* Current line length. */
	int max;               /* Maximal length seen so far. */
	char line[MAXLINE];    /* Current input line. */
	char longest[MAXLINE]; /* Longest line saved here. */

	max = 0;
	while ((len = getaline(line, MAXLINE)) > 0) {
		if (len == MAXLINE - 1 && line[MAXLINE - 2] != '\n')
			len = len + morelength();
		if (len > max) {
			max = len;
			copy(longest, line);
		}
	}
	if (max > 0) /* There was a line. */
		printf("Longest line: %d characters\n%s\n", max, longest);

	return 0;
}
```

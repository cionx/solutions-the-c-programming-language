# Exercise 1-16

> Revise the main routine of the longest-line program so it will correctly print the length of arbitrary long input lines, and as much as possible of the text.



For lines that are shorter than `MAXLEN - 1` we don’t need to change anything.
But for larger lines we have the problem that `getline` (which we renamed to `getaline` to avoid conflicts with `stdio`) doesn’t read the entire line.
But we need to know how many characters are still left in this long line.

To this end, we introduce an auxiliary function:
```c
/* counts additional length */
int morelength(void)
{
	int c;
	int counter;

	c = 0;
	counter = 0;
	while ((c = getchar()) != '\n' && c != EOF)
		++counter;

	return counter;
}
```
This function simply counts how many more characters there are until the next linebreak, or `EOF` (even though the `EOF` case should never occur).
We can detect if `getaline` left characters in the current line by checking if the length returned by `getaline` is `MAXLEN - 1` (so that `getaline` used up the entire space of `line`) and the second to last character is not a newline character.

This leads to the following modified main function:
```c
int main(void)
{
	int len;                /* current line length */
	int max;                /* maximal length seen so far */
	char line[MAXLINE];     /* current input line */
	char longest[MAXLINE];  /* longest line saved here */

	max = 0;
	while ((len = getaline(line, MAXLINE)) > 0) {
		if (len == MAXLINE - 1 && line[MAXLINE - 2] != '\n')
			len = len + morelength();
		if (len > max) {
			max = len;
			copy(longest, line);
		}
	}
	if (max > 0) /* there was a line */
		printf("Longest line: %d characters\n%s\n", max, longest);
	return 0;
}
```

# Exercise 1-12

> Write a program that prints its input one word per line.

---

We distinguish between two kinds of characters:
blanks, tabs and newlines are _separators_, all other characters are _word characters_.
We proceed as follows:

- Every non-separating character is simply printed to the output.

- When encountering a separator we have two cases to consider:

    - If we are exiting a word, then we have to follow up the last word character by a newline.

    - If we are not exiting a word, then this means that we encountered multiple separators right after one another.
      We must be careful to nevertheless print only one newline character.

  We thus need to keep track of whether we are currently exiting a word.
  We use a variable `position` to keep track of whether we are currently inside a word.

We get the following code:
```c
#include <stdio.h>

#define OUTSIDE 0
#define INSIDE  1

int main(void)
{
	int c;
	int position;

	c = 0; /* Dummy initial value. */
	position = OUTSIDE;
	while ((c = getchar()) != EOF) {
		if (c == ' ' || c == '\t' || c == '\n') {
			if (position == INSIDE) {
				putchar('\n');
				position = OUTSIDE;
			}
		}
		else {
			putchar(c);
			position = INSIDE;
		}
	}
}
```

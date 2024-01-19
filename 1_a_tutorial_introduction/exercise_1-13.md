# Exercise 1-13

> Write a program to print a histogram of the lengths of words in its input.
> It is easy to draw the histogram with the bars horizontal;
> a vertical orientation is more challenging.

---

### Counting

We will need to read and examine characters that we get from `getchar`.
For this, we use a variable `c`, which we will initialize with value `0`:
```c
int c;

⋮

c = 0; /* Dummy initial value. */

⋮
```

We need to know when to start counting the length of a word, and when to stop.
To this end we use a variable `state` that keeps track on whether we are inside a word or not, and that start off outside.
```c
#define OUTSIDE     0
#define INSIDE      1

⋮

int state;

⋮

state = OUTSIDE;

⋮
```

We will keep track of two lengths:
the length of the word that we are currently inside, and (for printing at the end) the maximal length that we have encountered so far.
Both variables will start off as `0` as we start outside any word, and haven’t encountered any word yet.
```c
⋮

int longest, cur_len;

⋮

longest = cur_len = 0;

⋮
```

We need to keep track of all the word lengths we have encountered so far.
We will use an array `count`, whose `len`-th entry tells us how many words of length `len` we have encountered so far.
However, there is a problem here:
the size of `count` is an upper limit to the lengths of words that we can record.
For the sake of this exercise we declare a maximal supported word length, and we will print a warning if a longer word is encountered.
```c
⋮

#define MAX_LEN     100

⋮

int count[MAX_LEN + 1];

⋮

for (int len = 0; len <= MAX_LEN; ++len)
	count[len] = 0;

⋮
```

As we go through the input, we have to make the following decisions for each character `c`:

- If `c` is none of the word-separating characters (blank, tab, newline), then we increment `cur_len` and update the `state` to `INSIDE`.
  (Strictly speaking, we only need to change `state` to `INSIDE` if it is currently `OUTSIDE`.
  This would require us to replace the single assignment `state = INSIDE` by the single check `state == OUTSIDE` and the sometimes-assignment `state = INSIDE`.
  This makes the code more complicated and probably gives not much improvement, if any.)

- If `c` is a word-separating character, then we have to check if we just ended a word.

  - If the current `state` is `OUTSIDE`, then we do nothing.

  - If `state` is `INSIDE`, then we just exited a word, and so must incorporate the length of this word in `count`.
    We also update `longest` if we have encountered a new longest word length.
    Afterwards, we set our state to `OUTSIDE` and also reset `cur_len` back to `0`.

We get the following code fragment:
```c
⋮

while ((c = getchar()) != EOF) {
	if (c == ' ' || c == '\t' || c == '\n') {
		/* Check if we’re exiting a word. */
		if (state == INSIDE) {
			if (cur_len > MAX_LEN) {
				printf("Warning: cannot handle words longer than %d. "
				       "Encountered length %d.",
				       MAX_LEN, cur_len);
			}
			else {
				++count[cur_len];
				if (cur_len > longest)
					longest = cur_len;
			}
			cur_len = 0;
			state = OUTSIDE;
		}
	}
	else {
		++cur_len;
		state = INSIDE;
	}
}

⋮
```



### Printing

We implement two types of printing:
first a horizontal histogram and then a vertical one.

#### Horizontal histogram

The horizontal histogram will look as follows:
```text
Horizontal Histogram
--------------------
 1   *******
 2   ********
 3   ****
 4   ******
 5   ***
 6   *
 7   **
 8   **
 9   **
10
11   **
12   *
```
The vertical histogram will look as follows:
```text
Vertical Histogram
------------------
    *
 *  *
 *  *     *
 *  *     *
 *  *  *  *
 *  *  *  *  *
 *  *  *  *  *     *  *  *     *
 *  *  *  *  *  *  *  *  *     *  *

 1  2  3  4  5  6  7  8  9 10 11 12
```

To properly align the printed lengths we need to know the maximal number of digits that a number from `1` to `longest` has.
For this we need to find out how often the longest of these numbers (in terms of digits) is divisible by 10:
```c
	int width = 0;
	for (int tmp = longest; tmp > 0; tmp = tmp / 10)
		++width;
```
The actual printing will then be a direct application of `for`-loops.

### The code

The overall code is as follows:
```c
#include <stdio.h>

#define OUTSIDE 0
#define INSIDE  1

#define MAX_LEN 100

int main(void)
{

	int longest, cur_len;
	int count[MAX_LEN + 1];

	int c;
	int state;

	for (int len = 0; len <= MAX_LEN; ++len)
		count[len] = 0;

	longest = cur_len = 0;

	/*** Counting of words ***/

	c = 0; /* Dummy initial value. */
	state = OUTSIDE;

	while ((c = getchar()) != EOF) {
		if (c == ' ' || c == '\t' || c == '\n') {
			/* Check if we’re exiting a word. */
			if (state == INSIDE) {
				if (cur_len > MAX_LEN) {
					printf("Warning: cannot handle words longer than %d. "
					       "Encountered length %d.",
					       MAX_LEN, cur_len);
				}
				else {
					++count[cur_len];
					if (cur_len > longest)
						longest = cur_len;
				}
				cur_len = 0;
				state = OUTSIDE;
			}
		}
		else {
			++cur_len;
			state = INSIDE;
		}
	}

	/*** Printing ***/

	/* We determine the number of digits of the longest occuring length.
	 * In the horizontial histogram, this is the width of the legend.
	 * In the vertical histogram, it is the width of the columns. */
	int width = 0;
	for (int tmp = longest; tmp > 0; tmp = tmp / 10)
		++width;

	/** Horizontal histogram **/

	printf("\nHorizontal Histogram\n--------------------\n");
	for (int len = 1; len <= longest; ++len) {
		printf("%*d   ", width, len);
		for (int i = 0; i < count[len]; ++i)
			putchar('*');
		putchar('\n');
	}

	printf("\n\n");

	/** Vertical histogram **/

	int highest = 0;
	for (int len = 0; len <= longest; ++len)
		if (count[len] > highest)
			highest = count[len];

	printf("\nVertical Histogram\n------------------\n");
	for (int height = highest; height > 0; --height) {
		for (int len = 1; len <= longest; ++len) {
			char symbol;
			if (count[len] >= height)
				symbol = '*';
			else
				symbol = ' ';
			printf("%*c", width, symbol);
			putchar(' '); /* Space between columns. */
		}
		putchar('\n');
	}
	putchar('\n'); /* Space between columns and legend. */
	for (int len = 1; len <= longest; ++len)
		printf("%*d ", width, len);
	putchar('\n');
}
```

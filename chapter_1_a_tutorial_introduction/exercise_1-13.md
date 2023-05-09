# Exercise 1-13

> Write a program to print a histogram of the lengths of words in its input.
> It is easy to draw the histogram with the bars horizontal;
> a vertical orientation is more challenging.



### Counting

We will need to read and examine characters that we get from `getchar`.
For this, we use a variable `c`, which we will initialize with value `0`:
```c
int c;

⋮

c = 0;

⋮
```

We need to know when to start counting the length of a word, and when to stop.
To this end we use a variable `state` that keeps track on whether we are inside a word or not, and start off outside.
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
the length of the word that we are currently inside, and (for printing at the end) the longest length we have encountered so far.
Both variables well start off as `0` as we start outside any word, and haven’t encountered any word yet.
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
(For example, if `count` is of size `20`, then we’d run into a problem if we encounter a word of length `30`.)

Originally we tried to “resize” `count` if this problem were to occur.
More precisely, we created a new array `new_count` that has double the size of `count`, copied the entries of `count` into `new_count`, and initialize all the new entries as `0`.
However, replacing `count` with the newly created `new_count` seems to require pointers, which we haven’t met yet.

We’ll therefore use a worse, but hopefully sufficient approach:
we define a maximum supported word length, and print a warning if a longer word is encountered.
```c
⋮

#define MAX_LEN     100

⋮

int count[MAX_LEN + 1];

⋮

for (int i = 0; i <= MAX_LEN; ++i)
	count[i] = 0;

⋮
```

As we go through the input, we have to make the following decisions for each character `c`:

- If `c` is none of the word-separating characters (blank, tab, newline), then we increment `cur_len` and update the `state` to `INSIDE`.
  (Strictly speaking, we only need to change `state` to `INSIDE` if it is currently `OUTSIDE`.
  This would require us to replace the single assignment `state = INSIDE` by the single check `state == OUTSIDE` and the sometimes-assignment `state = INSIDE`.
  This makes the code more complicated and probably gives not much improvement, if any.)

- If `c` is a word-separating character then we have to check if we just ended a word.

  - If the current `state` is `OUTSIDE`, then we’ll do nothing.

  - If `state` is `INSIDE`, then we have just endeded a word, and so must incorporate the length of this word in `count`.
    We also update `longest` if we have found a new longest word length.
    Afterwards, we set our state to `OUTSIDE` and also reset `cur_len` back to `0`.

We get altogether the following first part of the program:



### Printing

We implement two types of printing:
first as a horizontal histogram and then as a vertical one.

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
For this we need to find out how often the longest of these numbers (in terms of digits) is divisible by `10`:
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

#define OUTSIDE     0
#define INSIDE      1

#define MAX_LEN     100

int main(void)
{

	int longest, cur_len;
	int count[MAX_LEN + 1];

	int c;
	int state;

	int width; // needed later for printing

	for (int i = 0; i <= MAX_LEN; ++i)
		count[i] = 0;

	longest = cur_len = 0;

	/*** Counting of words ***/
	
	c = 0;
	state = OUTSIDE;

	while((c = getchar()) != EOF) {
		if (c == ' ' || c == '\t' || c == '\n') {
			if (state == INSIDE) {
				if (cur_len > MAX_LEN) {
					printf("Warning: cannot handle words longer than %d: lenght %d", MAX_LEN, cur_len);
				}
				else {
					++count[cur_len];
					if (cur_len > longest)
						longest = cur_len;
					cur_len = 0;
					state = OUTSIDE;
				}
			}
		}
		else {
			++cur_len;
			state = INSIDE;
		}
	}

	/*** Printing ***/
	
	width = 0;
	for (int tmp = longest; tmp > 0; tmp = tmp / 10)
		++width;

	/* Horizontal histogram */
	
	printf("\nHorizontal Histogram\n--------------------\n");
	for (int len = 1; len <= longest; ++len) {
		printf("%*d   ", width, len);
		for (int i = 0; i < count[len]; ++i)
			putchar('*');
		putchar('\n');
	}

	/* Vertical histogram */

	printf("\nVertical Histogram\n------------------\n");
	for (int height = longest; height > 0; --height) {
		for (int i = 1; i <= longest; ++i) {
			char symbol;
			if (count[i] >= height)
				symbol = '*';
			else
				symbol = ' ';
			printf("%*c", width, symbol);
			putchar(' '); // space between columns
		}
		putchar('\n');
	}
	putchar('\n'); // space between columns and legend
	for (int len = 1; len <= longest; ++len)
		printf("%*d ", width, len);
	putchar('\n');
}
```

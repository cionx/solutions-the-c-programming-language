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

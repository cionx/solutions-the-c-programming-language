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

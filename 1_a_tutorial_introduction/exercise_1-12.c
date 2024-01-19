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

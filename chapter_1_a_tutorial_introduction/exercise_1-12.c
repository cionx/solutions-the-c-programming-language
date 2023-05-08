#include <stdio.h>

#define NEWLINE 0
#define INLINE  1

int main(void)
{
	int c;
	int position;

	c = 0;
	position = NEWLINE;
	while ((c = getchar()) != EOF) {
		if (c == ' ' | c == '\t' | c == '\n') {
			if (position == INLINE) {
				putchar('\n');
				position = NEWLINE;
			}
		}
		else {
			putchar(c);
			position = INLINE;
		}
	}
}

#include <stdio.h>

int main(void)
{
	int c;

	c = 0;
	
	while ((c = getchar()) != EOF) {
		putchar(c);
		if (c == ' ') {
			while ((c = getchar()) == ' ')
				;
			putchar(c);
		}
	}
}

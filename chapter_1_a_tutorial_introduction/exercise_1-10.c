#include <stdio.h>

int main(void)
{
	int c;

	c = 0;
	while ((c = getchar()) != EOF) {
		if (c == '\t')
			printf("\\t");
		if (c != '\t') {
			if (c == '\b')
				printf("\\b");
			if (c != '\b') {
				if (c == '\\')
					printf("\\\\");
				if (c != '\\')
					putchar(c);
			}
		}
	}
}

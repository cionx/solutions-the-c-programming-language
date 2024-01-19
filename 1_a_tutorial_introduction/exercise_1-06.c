#include <stdio.h>

int main(void)
{
	int c = 'a'; /* An initial value that is not EOF. */
	while (c != EOF) {
		c = getchar();
		printf("The character %d gives %d\n", c, c != EOF);
	}
}

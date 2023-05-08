#include <stdio.h>
#include <stdbool.h>

int main(void)
{
	while (true) {
		printf("%d\n", getchar() != EOF);
	}
}

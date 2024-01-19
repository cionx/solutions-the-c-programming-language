#include <stdio.h>

/* 33 is exclamation mark, 126 is tilde */
#define START 33
#define END   126

int main(void)
{
	int c;
	int count[END + 1];
	int total;

	for (int i = 0; i <= END; ++i)
		count[i] = 0;
	total = 0;

	c = 0;
	while ((c = getchar()) != EOF) {
		if (START <= c && c <= END) {
			++count[c];
			++total;
		}
	}

	if (total == 0) {
		printf("Error: no characters found");
	}
	else {
		printf("ASCII  CHAR  FREQ %%\n");
		printf("-----  ----  ------\n");
		for (int i = START; i <= END; ++i) {
			if (count[i] != 0) {
				float freq_percent;
				freq_percent = 100.0 * count[i] / total;
				printf("  %3d     %c   %5.2f   ", i, i, freq_percent);
				/* We print as many stars as the frequency in percent rounded to
				 * the nearest integer. So, below 0.5 no star, from 0.5 to 1.5
				 * one star, from 1.5 to 2.5 two stars, and so on. */
				for (float p = 0.5; p <= freq_percent; ++p)
					putchar('*');
				putchar('\n');
			}
		}
	}
}

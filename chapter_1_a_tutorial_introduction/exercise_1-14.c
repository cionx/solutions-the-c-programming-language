#include <stdio.h>

#define START   33
#define END     126

int main(void)
{
	int c;
	int count[END - START + 1];
	int total;

	for (int i = 0; i < END - START + 1; ++i)
		count[i] = 0;
	total = 0;

	c = 0;
	while ((c = getchar()) != EOF) {
		// 32 is blank, 126 is ~
		if (START <= c && c <= END) {
			++count[c - START];
			++total;
		}
	}

	if (total == 0) {
		printf("Error: no characters found");
	}
	else {
		printf("ASCII  CHAR  FREQ\n");
		printf("-----  ----  ----\n");
		for (int i = 0; i < END - START + 1; ++i) {
			if (count[i] != 0) {
				float freq_perc;
				freq_perc = (100.0 * count[i]) / total;
				printf("  %3d     %c  %4.1f  ", i + START, i + START, freq_perc);
				for (int n = 0; n <= freq_perc; ++n)
					putchar('*');
				putchar('\n');
			}
		}
	}
}

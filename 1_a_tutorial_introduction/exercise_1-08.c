#include <stdio.h>

int main(void)
{
	int c;
	long count_blank, count_tab, count_newline;

	count_blank = count_tab = count_newline = 0;
	while ((c = getchar()) != EOF) {
		if (c == ' ')
			++count_blank;
		if (c == '\t')
			++count_tab;
		if (c == '\n')
			++count_newline;
	}

	printf("Blanks: %ld\n", count_blank);
	printf("Tabs:   %ld\n", count_tab);
	printf("Lines:  %ld\n", count_newline);
}

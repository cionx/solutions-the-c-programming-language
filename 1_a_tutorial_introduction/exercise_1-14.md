# Exercise 1-14

> Write a program to print a histogram of the frequencies of different characters in its input.



We decided to count all printable ASCII characters.
The output will be formatted as follows:
```text
ASCII  CHAR  FREQ
-----  ----  ----
   35     #   1.1  **
   46     .   2.2  ***
   49     1   2.2  ***
   52     4   1.1  **
   62     >   1.1  **
   69     E   1.1  **
   87     W   1.1  **
   97     a   6.5  *******
   99     c   4.3  *****
  100     d   1.1  **
  101     e  10.9  ***********
  102     f   5.4  ******
  103     g   2.2  ***
  104     h   3.3  ****
  105     i   9.8  **********
  109     m   2.2  ***
  110     n   5.4  ******
  111     o   5.4  ******
  112     p   3.3  ****
  113     q   1.1  **
  114     r  10.9  ***********
  115     s   5.4  ******
  116     t   9.8  **********
  117     u   2.2  ***
  120     x   1.1  **
```
We use the following code:
```c
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
```

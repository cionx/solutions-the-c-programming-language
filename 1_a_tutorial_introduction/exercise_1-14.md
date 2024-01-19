# Exercise 1-14

> Write a program to print a histogram of the frequencies of different characters in its input.

---

We count all printable ASCII characters.
The output will be formatted as follows:
```text

ASCII  CHAR  FREQ %
-----  ----  ------
   44     ,    1.63   **
   46     .    1.22   *
   65     A    0.41   
   76     L    0.81   *
   83     S    0.41   
   97     a    8.94   *********
   98     b    1.22   *
   99     c    2.44   **
  100     d    5.28   *****
  101     e   11.38   ***********
  103     g    1.63   **
  105     i    6.10   ******
  106     j    0.41   
  107     k    0.81   *
  108     l    3.66   ****
  109     m    6.50   *******
  110     n    4.07   ****
  111     o    8.54   *********
  112     p    2.03   **
  113     q    0.41   
  114     r    6.50   *******
  115     s    7.32   *******
  116     t   10.16   **********
  117     u    6.10   ******
  118     v    1.22   *
  121     y    0.81   *
```
Our code is as follows:
```c
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
				float freq_perc;
				freq_perc = 100.0 * count[i] / total;
				printf("  %3d     %c   %5.2f   ", i, i, freq_perc);
				/* We print as many stars as the frequency in percent rounded to
				 * the nearest integer. So, below 0.5 no star, from 0.5 to 1.5
				 * one star, from 1.5 to 2.5 two stars, and so on. */
				for (float p = 0.5; p <= freq_perc; ++p)
					putchar('*');
				putchar('\n');
			}
		}
	}
}
```

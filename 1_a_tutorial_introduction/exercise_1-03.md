# Exercise 1-3

> Modify the temperature conversion program to print a heading above the table.

---

We add the following two lives above the `while` loop:
```c
printf("Fahrenheit Celsius\n");
printf("---------- -------\n");
```
We also modify the printing of the calculated values as follows:
```c
printf("      %3.0f  %6.1f\n", fahr, celsius);
```
This leads overall to the following code:
```c
#include <stdio.h>

/* print Fahrenheit-Celsius table
   for fahr = 0, 20, ..., 300; floating-point version */
int main(void)
{
	float fahr, celsius;
	int lower, upper, step;

	lower = 0;   /* lower limit of temperature table */
	upper = 300; /* upper limit */
	step = 20;   /* step size */

	printf("Fahrenheit Celsius\n");
	printf("---------- -------\n");
	fahr = lower;
	while (fahr <= upper) {
		celsius = (5.0 / 9.0) * (fahr - 32.0);
		printf("      %3.0f  %6.1f\n", fahr, celsius);
		fahr = fahr + step;
	}
}
```
The output of this program is as follows:
```text
Fahrenheit Celsius
---------- -------
        0   -17.8
       20    -6.7
       40     4.4
       60    15.6
       80    26.7
      100    37.8
      120    48.9
      140    60.0
      160    71.1
      180    82.2
      200    93.3
      220   104.4
      240   115.6
      260   126.7
      280   137.8
      300   148.9
```

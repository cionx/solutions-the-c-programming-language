# Exercise 1-4

> Write a program to print the corresponding Celsius to Fahrenheit table.

---

We can rearrange the equation
$$
  \mathrm{Celsius} = \frac{5}{9} (\mathrm{Fahrenheit} - 32)
$$
to
$$
  \mathrm{Fahrenheit} = \frac{9}{5} \mathrm{Celsius} + 32 \,.
$$
This leads to the following code:
```c
#include <stdio.h>

/* print Fahrenheit-Celsius table
   for fahr = 0, 20, ..., 300; floating-point version */
int main(void)
{
	float fahr, celsius;
	int lower, upper, step;

	lower = -20; /* lower limit of temperature table */
	upper = 150; /* upper limit */
	step = 10;   /* step size */

	printf("Celsius Fahrenheit\n");
	printf("------- ----------\n");
	celsius = lower;
	while (celsius <= upper) {
		fahr = (9.0 / 5.0) * celsius + 32.0;
		printf("   %3.0f     %6.1f\n", celsius, fahr);
		celsius = celsius + step;
	}
}
```
The output is as follows:
```text
Celsius Fahrenheit
------- ----------
   -20       -4.0
   -10       14.0
     0       32.0
    10       50.0
    20       68.0
    30       86.0
    40      104.0
    50      122.0
    60      140.0
    70      158.0
    80      176.0
    90      194.0
   100      212.0
   110      230.0
   120      248.0
   130      266.0
   140      284.0
   150      302.0
```

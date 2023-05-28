# Exercise 1-15

> Rewrite the temperature conversion program of Section 1.2 to use a function for conversion.



We get the following code:
```c
#include <stdio.h>

/* print Fahrenheit-Celsius table *
 * for fahr = 0, 20, ..., 300     */

#define LOWER 0
#define UPPER 300
#define STEP  20

float celsius(float fahr);

int main(void)
{
	for(int fahr = LOWER; fahr <= UPPER; fahr = fahr + STEP)
		printf("%3d %6.1f\n", fahr, celsius(fahr));
}

float celsius(float fahr)
{
	return (5.0 / 9.0) * (fahr - 32);
}
```

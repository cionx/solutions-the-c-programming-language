# Exercise 1-6

> Verify that the expression `getchar() != EOF` is 0 or 1.



We tried to use the following code:
```c
#include <stdio.h>
#include <stdbool.h>

int main(void)
{
	while (true) {
		printf("%d\n", getchar() != EOF);
	}
}
```
We get the following behaviour:

- With Ctrl+C, the program exits.

- With Ctrl+D, the program prints `0` in an infinite loop.
  We suspect that `getchar` keeps returning `EOF` over and over again.

- With every other character that we tested, the program prints `1`.

We used `stdbool.h` to be able to use `true`.

Our program seems to support the claim that `getchar() != EOF` is always 0 or 1.

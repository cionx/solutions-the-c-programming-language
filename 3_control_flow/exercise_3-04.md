# Exercise 3-4

> In a two’s complement number representation, our version of `iota` does not handle the largest negative number, that is, the value of `n` equal to $-(2^{\textrm{wordsize} - 1})$.
> Explain why not.
> Modify it to print that value correctly, regardless of the machine on which it runs.

---

The problem lies in the following two lines:
```c
if ((sign = n) < 0)
	n = -n;
```
The range of `int` goes from $-2^{\textrm{wordsize} - 1}$ to $2^{\textrm{wordsize}} - 1$.
If `n` has the value $-2^{\textrm{wordsize} - 1}$, then by passing from $n$ to $-n$ an overflow happens, and we are back to the negative value $-2^{\textrm{wordsize} - 1}$.[^1]

The `%`-operator has the property that `(-n) % 10` equals `-(n % 10)` for sensible values of `n`.
For example, `-123 % 10` equals `-3`.
We can therefore proceed with only two small changes:

- Instead of making `n` positive, we always make it negative.
- We replace `n % 10` by `-(n % 10)`.

We thus arrive at the following modified code:
```c
#include <stdbool.h>
#include <string.h>

/* itoa(n, s): convert n to characters in s */
void itoa(int n, char s[])
{
	bool negative = (n < 0);
	if (n > 0)
		n = -n;

	int i = 0;
	do {
		s[i++] = -(n % 10) + '0';
	} while ((n /= 10) != 0);

	if (negative)
		s[i++] = '-';

	s[i] = '\0';
	reverse(s);
}
```

We test our function as follows:
```c
#include <limits.h>
#include <stdio.h>

int main(void)
{
	int numbers[] = {123, -123, 0, INT_MAX, INT_MIN};
	int length = 5;
	char s[100];

	for (int i = 0; i < length; ++i) {
		itoa(numbers[i], s);
		printf("%d becomes \"%s\"\n", numbers[i], s);
	}

	return 0;
}
```
The output seems to be correct:
```text
123 becomes "123"
-123 becomes "-123"
0 becomes "0"
2147483647 becomes "2147483647"
-2147483648 becomes "-2147483648"
```

[^1]: This explanation is actually not quite true: overflow/underflow of signed values is undefined behaviour.

# Exercise 3-4

> In a two’s complement number representation, our version of `iota` does not handle the largest negative number, that is, the value of `n` equal to $-(2^{\textrm{wordsize} - 1})$.
> Explain why not.
> Modify it to print that value correctly, regardless of the machine on which it runs.



The problem lies in the following two lines:
```c
if ((sign = n) < 0)
	n = -n;
```
The range of `int` goes from $-2^{\textrm{wordsize} - 1}$ to $2^{\textrm{wordsize}} - 1$.
If `n` has the value $-2^{\textrm{wordsize} - 1}$, then by passing from $n$ to $-n$ an overflow happens, and we are back to the negative value $-2^{\textrm{wordsize} - 1}$.

To circumvent this problem we add another loop:
we will work with (potentially) negative results for modulo until we get to the point where we can safely pass from `n` to `-n`.
(This will actually be the case after at most one iteration.)

For example, `(-123) % 10` is `-3`, and by flipping the sign we get the digit `3`.
We then replace `-123` with `(-123) / 10 = -12` and continue on with the original procedure.

```c
/* itoa: convert n to characters in s */
void itoa(int n, char s[])
{
	int i = 0;
	bool sign = (n < 0);

	/* Calculate digits using negative modulo until there is no overflow.
	 * This also takes care of the digit for n = 0.
	 */
	do {
		int mod = n % 10;
		if (mod < 0)
			mod = -mod;
		s[i++] = (char) mod + '0';
		n /= 10;
	} while (n < 0 && -n < 0); /* Should always fail. */
	/* Make n non-negative. */
	if (n < 0)
		n = -n;
	/* Generate the digits in reverse order. */
	for (; n > 0; n /= 10)
		s[i++] = n % 10 + '0';
	if (sign)
		s[i++] = '-';
	s[i] = '\0';

	reverse(s);
}
```

We test our code as follows:
```c
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

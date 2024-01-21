# Exercise 3-5

> Write the function `itob(n,s,b)` that converts the integer `n` into a base `b` character representation in the string `s`.
> In particular, `itop(n,s,16)` formats `n` as a hexadecimal integer in `s`.

---

We take our code from the previous exercise and make the following changes to it:

- We replace `10` by `b`.
- Instead of `mod + '0'` we use an auxiliary function `digit(mod)`.
  The argument `mod` is required to be non-negative.
  For the input `0, 1, 3, ...` the output will be `'0', '1', ..., '9', 'A', 'B', ...`

```c
/* itob(n, s, b): convert n to characters in s with base b */
void itob(int n, char s[], int b)
{
	bool negative = (n < 0);
	if (n > 0)
		n = -n;

	int i = 0;
	do {
		s[i++] = digit(-(n % b));
	} while ((n /= b) != 0);

	if (negative)
		s[i++] = '-';

	s[i] = '\0';
	reverse(s);
}

/* digit(n): n is required to be non-negative.
 * The output is '0', '1', ..., '9', 'A', 'B', ...
 * Should only be used for 0 <= n <= 35
 */
char digit(int n)
{
	if (0 <= n && n <= 9)
		return (char) n + '0';
	else if (10 <= n)
		return (char) (n - 10) + 'A';
	return -1;
}
```

For the test cases `123, -123, 0, INT_MAX, INT_MIN` we get the following output for base 16:
```text
123 becomes "7B"
-123 becomes "-7B"
0 becomes "0"
2147483647 becomes "7FFFFFFF"
-2147483648 becomes "-80000000"
```
We also get the following output for base 2:
```text
123 becomes "1111011"
-123 becomes "-1111011"
0 becomes "0"
2147483647 becomes "1111111111111111111111111111111"
-2147483648 becomes "-10000000000000000000000000000000"
```

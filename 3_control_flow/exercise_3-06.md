# Exercise 3-6

> Write a version of `itoa` that accepts three arguments instead of two.
> The third argument is a minimum field width;
> the converted number must be padded with blanks on the left if necessary to make it wide enough.



We modify our code from Exercise 3-4.
We add the additional parameter `width` to `itoa`.
We decrement `width` every time we add a character to `s`.
Before reversing `s` we add `width` many blanks, for whatever `width` is at this point.
If `width` has become non-positive, then no blanks are added.

```c
/* itoa: convert n to characters in s with minimal width */
void itoa(int n, char s[], int width)
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
		--width;
	} while (n < 0 && -n < 0); /* Should always fail. */
	/* Make n non-negative. */
	if (n < 0)
		n = -n;
	/* Generate the digits in reverse order. */
	for (; n > 0; n /= 10, --width)
		s[i++] = n % 10 + '0';
	if (sign) {
		s[i++] = '-';
		--width;
	}
	for (; width > 0; --width)
		s[i++] = ' ';
	s[i] = '\0';

	reverse(s);
}
```

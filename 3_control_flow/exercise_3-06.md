# Exercise 3-6

> Write a version of `itoa` that accepts three arguments instead of two.
> The third argument is a minimum field width;
> the converted number must be padded with blanks on the left if necessary to make it wide enough.

---

We modify our code from Exercise 3-4.
We add the additional parameter `width` to `itoa`.
We decrement `width` every time we add a character to `s`.
Before reversing `s` we add `width` many blanks, for whatever `width` remains.
If `width` has become non-positive, then no blanks are added.

```c
/* itoa(n, s, w): convert n to characters in s with minimal width w */
void itoa(int n, char s[], int width)
{
	bool negative = (n < 0);
	if (n > 0)
		n = -n;

	int i = 0;
	do {
		s[i++] = -(n % 10) + '0';
		--width;
	} while ((n /= 10) != 0);
	if (negative)
		s[i++] = '-';

	for (; width > 0; --width)
		s[i++] = ' ';

	s[i] = '\0';
	reverse(s);
}
```

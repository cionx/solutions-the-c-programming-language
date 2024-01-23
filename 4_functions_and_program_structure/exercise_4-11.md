# Exercise 4-11

> Modify `getop` so that it doesn’t need to use `ungetch`.
> Hint: use an internal static variable.

---

Without `ungetch` there is no need for using the buffer, so we might also replace the usage of `getch` by `getchar`.
We use two static internal variables to keep track of the additional character, and whether such a character is there at all.
We thus arrive at the following version for `getop`:
```c
#include <stdbool.h>

/* getop(s): get next operator or numeric operand */
int getop(char s[])
{
	int i, c;

	static int buffer = ' ';      /* Dummy value. */
	static bool buffered = false; /* Nothing buffered before the first call. */

	if (buffered) {
		c = buffer;
		buffered = false;
	}
	else
		c = getchar();

	while ((s[0] = c) == ' ' || c == '\t') /* skip whitespace */
		c = getchar();
	s[1] = '\0';

	if (!isdigit(c) && c != '.')
		return c;   /* not a number */

	i = 0;
	if (isdigit(c)) /* collect integer part */
		while (isdigit(s[++i] = c = getchar()))
			;
	if (c == '.')   /* collect fraction part */
		while (isdigit(s[++i] = c = getchar()))
			;
	s[i] = '\0';
	if (c != EOF) {
		buffer = c;
		buffered = true;
	}
	return NUMBER;
}
```

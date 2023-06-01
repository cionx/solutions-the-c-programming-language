# Exercise 3-3

> Write a function `expand(s1, s2)` that expands shorthand notations like `a-z` in the string `s1` into the equivalent complete list `abc...xyz` in `s2`.
> Allow for letters of either case and digit, and be prepared to handle cases like `a-b-c` and `a-z0-9` and `-a-z`.

For the most part, we simply copy the characters from `s1` into `s2`.
But when we encounter a hyphen, then we check if it is placed between two characters `c1` and `c2` of the same kind (digits, lowercase letters, uppercase letters).
We use the functions provided in `ctype.h` for these tests.

If one of these checks is positive, then instead of copying the hyphen to `s2` we add all characters that lie strictly between `c1` and `c2` to `s2`.
If `c2` comes before `c1`, then we traverse all characters strictly between `c2` and `c1` (e.g., `9-0` is extended to `9876543210`).
For this purpose, we find out the direction in which we need to move via the conditional expression `(c1 <= c2) ? 1 : -1`.
```c
#include <ctype.h>

void expand(char s1[], char s2[])
{
	if ((s2[0] = s1[0]) == '\0')
		return;

	int j = 1;
	for (int i = 1; s1[i] != '\0'; ++i) {
		if (s1[i] != '-')
			s2[j++] = s1[i];
		else {
			char c1 = s1[i - 1]; /* Okay because i starts as 1. */
			char c2 = s1[i + 1];
			if ((isdigit(c1) && isdigit(c2)) || (islower(c1) && islower(c2)) ||
			    (isupper(c1) && isupper(c2))) {
				char direction = (c1 <= c2) ? 1 : -1;
				for (char c = c1 + direction; c != c2; c += direction)
					s2[j++] = c;
			}
			else
				s2[j++] = s1[i];
		}
		s2[j] = '\0';
	}
}
```

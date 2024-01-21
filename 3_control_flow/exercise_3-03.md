# Exercise 3-3

> Write a function `expand(s1, s2)` that expands shorthand notations like `a-z` in the string `s1` into the equivalent complete list `abc...xyz` in `s2`.
> Allow for letters of either case and digit, and be prepared to handle cases like `a-b-c` and `a-z0-9` and `-a-z`.

---

For the most part, we simply copy the characters from `source` into `target`.
But when we encounter a hyphen, then we check if it is placed between two characters `before` and `after` of the same kind (digits, lowercase letters, uppercase letters).
We use the functions provided in `ctype.h` for these tests.

If one of these checks is positive, then instead of copying the hyphen to `target` we add all characters that lie strictly (!) between `before` and `after` to `target`.
We note that if `after` comes before `before`, then we traverse all characters strictly between `after` and `before` (e.g., `9-0` is extended to `9876543210`).
For this purpose, we find out the direction in which we need to move via the conditional expression `(before <= after) ? 1 : -1`.
```c
#include <ctype.h>

void expand(char source[], char target[])
{
	if ((target[0] = source[0]) == '\0')
		return;

	int to = 1;
	for (int from = 1; source[from] != '\0'; ++from) {
		if (source[from] != '-')
			target[to++] = source[from];
		else {
			char before = source[from - 1]; /* Okay because from starts as 1. */
			char after = source[from + 1];
			if ((isdigit(before) && isdigit(after)) ||
			    (islower(before) && islower(after)) ||
			    (isupper(before) && isupper(after))) {
				char direction = (before <= after) ? 1 : -1;
				for (char c = before + direction; c != after; c += direction)
					target[to++] = c;
			}
			else
				target[to++] = '-';
		}
		target[to] = '\0';
	}
}
```

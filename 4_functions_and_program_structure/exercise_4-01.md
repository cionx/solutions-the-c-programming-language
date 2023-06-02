# Exercise 4-1

> Write a function `strrindex(s, t)`, which returns the position of the _rightmost_ occurrence of `t` in `s`, or `-1` if there is none.



The function `strrindex` goes backwards through `s`, and checks for each encountered character if is starts a substring that is equal to `t`.
```c
int strrindex(char s[], char t[])
{
	/* Find the end of s. */
	int i = 0;
	while (s[i] != '\0')
		++i;

	for (; i >= 0; --i) {
		/* Check if s[i] start a substring equal to t. */
		int k = 0;
		for (int j = i; s[j] == t[k] && t[k] != '\0'; ++j, ++k)
			;
		if (t[k] == '\0')
			return i;
	}

	return -1;
}
```

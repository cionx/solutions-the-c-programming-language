# Exercise 2.4

> Write an alternate version of `squeeze(s1, s2)` that deletes each character in `s1` that matches any character in the _string_ `s2`.

---

We can write the described function as follows:
```c
#include <stdbool.h>

void squeeze(char str1[], const char str2[])
{
	int from, to;
	for (from = to = 0; str1[from] != '\0'; ++from)
		if (!instring(str1[from], str2))
			str1[to++] = str1[from];
	str1[to] = '\0';
}

bool instring(char c, const char str[])
{
	for (int i = 0; str[i] != '\0'; ++i) {
		if (c == str[i])
			return true;
	}
	return false;
}
```

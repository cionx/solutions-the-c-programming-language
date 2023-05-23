# Exercise 2.4

> Write an alternate version of `squeeze(s1, s2)` that deletes each character in `s1` that matches any character in the _string_ `s2`.



We can write the described function as follows:
```c
#include <stdbool.h>

void squeeze(char str1[], char str2[])
{
	int i, j;
	for (i = j = 0; str1[i] != '\0'; ++i)
		if (!in_string(str1[i], str2))
			str1[j++] = str1[i];
	str1[j] = '\0';
}

bool in_string(char c, char str[])
{
	for (int i = 0; str[i] != '\0'; ++i) {
		if (c == str[i])
			return true;
	}
	return false;
}
```

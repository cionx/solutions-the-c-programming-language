# Exercise 2-5

> Write a function `any(s1, s2)`, which returns the first location in the string `s1` where any character from the string `s2` occurs, or `-1` if `s1` contains no characters from `s2`.
> (The standard library function `strpbrk` does the same job but returns a pointer to the location.)



We can write the described function as follows, where we reuse the auxiliary function `in_str` from the previous exercise:
```c
#include <stdbool.h>

int any(char str1[], char str2[]);
bool in_string(char c, char str[]);

int any(char str1[], char str2[])
{
	for (int i = 0; str1[i] != '\0'; ++i)
		if (in_string(str1[i], str2))
			return i;

	return -1;
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

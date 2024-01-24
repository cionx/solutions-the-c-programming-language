# Exercise 5-4

> Write the function `strend(s,t)`, which returns `1` if the string `t` occurs at the end of the string `s,` and zero otherwise.

---

We use two pointers, `u` and `v`, that point the ends of `s` and `t` respectively.
We then compare `u` and `v` while decrementing both pointers, until either
- a difference is found
- `u` has reached the start of `s`, or
- `v` has reached the start of `t`.
We then check that the third case occurred.
```c
#include <stdbool.h>

/* strend(s, t): checks if t as the end of s */
bool strend(char const *s, char const *t)
{
	const char *u = s, *v = t;
	while (*u != '\0')
		++u;
	while (*v != '\0')
		++v;

	while (s < u && t < v && *u == *v)
		--u, --v;
	return v == t && *u == *v;
}
```

We test our function with the following code:
```c
int main(void)
{
	char *s = "abcdef";
	char *t = "def";
	char *u = "cef";
	char *v = "fedcba";
	char *w = "abcdefg";
	printf("\"%s\" ends in \"%s\": %d\n", s, s, strend(s, s));
	printf("\"%s\" ends in \"%s\": %d\n", s, t, strend(s, t));
	printf("\"%s\" ends in \"%s\": %d\n", s, u, strend(s, u));
	printf("\"%s\" ends in \"%s\": %d\n", s, v, strend(s, v));
	printf("\"%s\" ends in \"%s\": %d\n", s, w, strend(s, w));
}
```
The output is as desired:
```text
"abcdef" ends in "abcdef": 1
"abcdef" ends in "def": 1
"abcdef" ends in "cef": 0
"abcdef" ends in "fedcba": 0
"abcdef" ends in "abcdefg": 0
```

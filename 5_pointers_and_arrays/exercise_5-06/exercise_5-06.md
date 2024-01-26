# Exercise 5-6

> Rewrite appropriate programs from earlier chapters and exercises with pointers instead of array indexing.
> Good possibilities include `getline` (Chapters 1 and 4), `atoi`, `itoa`, and their variants (Chapters 2, 3, and 4), `reverse` (Chapter 3), and `strindex` and `getop` (Chapter 4).

---



## `atoi`

The current code for `atoi`, from page 61, is as follows:
```c
#include <ctype.h>

/* atoi: convert s to integer; pointer version */
int atoi(char s[])
{
	int i, n, sign;

	for (i = 0; isspace(s[i]); i++) /* skip white space */
		;
	sign = (s[i] == '-') ? -1 : 1;
	if (s[i] == '+' || s[i] == '-') /* skip sign */
		i++;
	for (n = 0; isdigit(s[i]); i++)
		n = 10 * n + (s[i] - '0');
	return sign * n;
}
```
We only have to replace `s[i]` by `*s` and `i++` by `++s`.
```c
/* atoi: convert s to integer; pointer version */
int atoi(char s[])
{
	int n, sign;

	for (; isspace(*s); ++s)    /* skip white space */
		;
	sign = (*s == '-') ? -1 : 1;
	if (*s == '+' || *s == '-') /* skip sign */
		s++;
	for (n = 0; isdigit(*s); ++s)
		
		n = 10 * n + (*s - '0');
	return sign * n;
}
```

We test our code as follows:
```c
char *strings[] = {"123", "-123", "0", "-0"};
for (int i = 0; i < 4; ++i)
	printf("\"%s\" becomes %d.\n", strings[i], atoi(strings[i]));
```
The output is as desired:
```text
"123" becomes 123.
"-123" becomes -123.
"0" becomes 0.
"-0" becomes 0.
```



## `atof`

We can proceed similarly with `atof` from page 6.
The current code is as follows:
```c
#include <ctype.h>

/* atof: convert string s to double */
double atof(char s[])
{
	double val, power;
	int i, sign;

	for (i = 0; isspace(s[i]); i++) /* skip white space */
		;
	sign = (s[i] == '-') ? -1 : 1;
	if (s[i] == '+' || s[i] == '-')
		i++;
	for (val = 0.0; isdigit(s[i]); i++)
		val = 10.0 * val + (s[i] - '0');
	if (s[i] == '.')
		i++;
	for (power = 1.0; isdigit(s[i]); i++) {
		val = 10.0 * val + (s[i] - '0');
		power *= 10.0;
	}
	return sign * val / power;
}
```
The new code is then as follows:
```c
/* atof: convert string s to double; pointer version */
double atof(char s[])
{
	double val, power;
	int sign;

	for (; isspace(*s); ++s) /* skip white space */
		;
	sign = (*s == '-') ? -1 : 1;
	if (*s == '+' || *s == '-')
		s++;
	for (val = 0.0; isdigit(*s); s++)
		val = 10.0 * val + (*s - '0');
	if (*s == '.')
		s++;
	for (power = 1.0; isdigit(*s); s++) {
		val = 10.0 * val + (*s - '0');
		power *= 10.0;
	}
	return sign * val / power;
}
```

We test our function as follows:
```c
char *strings[] = {"123",     "-123",     "0",    "-0",
                   "123.456", "-123.456", ".456", "-.456"};
for (int i = 0; i < 8; ++i)
	printf("\"%s\" becomes %g.\n", strings[i], atof(strings[i]));
```
The result is as desired:
```text
"123" becomes 123.
"-123" becomes -123.
"0" becomes 0.
"-0" becomes -0.
"123.456" becomes 123.456.
"-123.456" becomes -123.456.
".456" becomes 0.456.
"-.456" becomes -0.456.
```



## `reverse`

We use the following code:
```c
/* reverse(s): reverse string s in place; pointer version */
void reverse(char *s)
{
	/* Handle the empty string by hand */
	if (*s == '\0')
		return;

	char *t = s;
	while (*t != '\0')        /* We have at least one iteration... */
		++t;
	--t;                      /* ... so that s <= t... */
	for (; s < t; ++s, --t) { /* ... allowing for pointer comparion. */
		char tmp;
		tmp = *s;
		*s = *t;
		*t = tmp;
	}
}
```

We test our code as follows:
```c
int main(void)
{
	char strings[][8] = {"",     "a",     "ab",     "abc",
	                     "abcd", "abcde", "abcdef", "abcdefg"};
	for (int i = 0; i < 8; ++i) {
		printf("\"%s\" becomes ", strings[i]);
		reverse(strings[i]);
		printf("\"%s\"\n", strings[i]);
	}

	return 0;
}
```
The output is as desired:
```text
"" becomes ""
"a" becomes "a"
"ab" becomes "ba"
"abc" becomes "cba"
"abcd" becomes "dcba"
"abcde" becomes "edcba"
"abcdef" becomes "fedcba"
"abcdefg" becomes "gfedcba"
```



## `itoa`

We use the same approach as in Exercise 3-4:
```c
void itoa(int n, char *s)
{
	char *const start = s;
	bool negative = (n < 0);

	if (n > 0)
		n = -n;
	do {
		*s++ = -(n % 10) + '0';
		n /= 10;
	} while (n != 0);
	if (negative)
		*s++ = '-';
	*s = '\0';
	reverse(start);
}
```

We test our function as follows:
```c
#include <limits.h>

int main(void)
{
	int nums[] = {123, -123, 0, INT_MAX, INT_MIN};
	char s[10];
	for (int i = 0; i < 5; ++i) {
		itoa(nums[i], s);
		printf("%d becomes \"%s\"\n", nums[i], s);
	}
}
```
The output is as follows:
```text
123 becomes "123"
-123 becomes "-123"
0 becomes "0"
2147483647 becomes "2147483647"
-2147483648 becomes "-2147483648"
```



## `strindex`

We implement `strindex` as follows:
```c
#include <stdbool.h>

int strindex(char const *s, char const *t);
bool startswith(char const *s, char const *t);

/* strindex(s, t): index of first occurrence of t in s */
int strindex(char const *s, char const *const t)
{
	char const *const start = s;
	for (; *s != '\0'; ++s)
		if (startswith(s, t))
			return (int) (s - start);
	if (*t == '\0')
		return 0;
	else
		return -1;
}

/* startswith(s, t): checks if s starts with t */
bool startswith(char const s[], char const t[])
{
	/* We go through s until we either found a difference or have gone through
	 * all of t. */
	while (*s == *t && *t != '\0')
		++s, ++t;
	return *t == '\0';
}
```
(We could implement `strstr` in the same way, by returning `s` instead of `s - start`.)

We test our function as follows:
```c
char const *const strings[][2] = {
	{"", ""},      {"", "a"},      {"a", ""},    {"a", "a"},
	{"abc", "a"},  {"abc", "b"},   {"abc", "c"}, {"abc", "ab"},
	{"abc", "bc"}, {"abc", "abc"}, {"abc", "d"}, {"abc", "ad"}};

for (int i = 0; i < 12; ++i) {
	char const *const s = strings[i][0];
	char const *const t = strings[i][1];
	printf("\"%s\" in \"%s\": %d\n", t, s, strindex(s, t));
}
```
The output seems to be correct:
```text
"" in "": 0
"a" in "": -1
"" in "a": 0
"a" in "a": 0
"a" in "abc": 0
"b" in "abc": 1
"c" in "abc": 2
"ab" in "abc": 0
"bc" in "abc": 1
"abc" in "abc": 0
"d" in "abc": -1
"ad" in "abc": -1
```



## `getline`

We can implement `getline` by
- replacing `s[i]` with `*s`,
- replacing `++i` with `++s`,
- replacing `i` with `s - start` where we set `start = s` at the very beginning of the function.
We thus arrive at the following code:
```c
/* getline: read a line into s, return length */
#include <stdio.h>

int getaline(char s[], int lim)
{
	int c;
	char *start = s;

	for (; s - start < lim - 1 && (c = getchar()) != EOF && c != '\n'; ++s)
		*s = c;
	if (c == '\n') {
		*s = c;
		++s;
	}
	*s = '\0';
	return s - start;
}```

We have not tested this function.

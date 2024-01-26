# Exercise 5-5

> Write versions of the library functions `strncpy`, `strncat`, and `strncmp`, which operate on at most the first `n` characters of their argument strings.
> For example, `strncpy(s,t,n)` copies at most `n` characters of `t` to `s.`
> Full descriptions are in Appendix B.

---

The functions in question are described as follows in Appendix B:


| function | description |
|:---------|:------------|
| `char *strncpy(s,t,n)`      | copy at most `n` characters of string `t` to `s`; return `s`. Pad with `\0` if `t` has fewer than `n` characters.
| `char *strncat(s,t,n)`      | concatenate at most `n` characters of string `t` to string `s`, terminate `s` with `\0`; return `s`.
| `int strncmp(s, t, n)`      | compare at most `n` characters of string `s` to string `t`; return `< 0` if `s < t`, `0` if `s == t`, or `> 0` if `s > t`.



## Code

### `strncpy`

We slightly alter the implementation of `strcpy` from page 106:
```c
char *my_strncpy(char *to, const char *from, int n)
{
	char *const start = to;

	while (n-- > 0 && (*to++ = *from++) != '\0')
		;
	while (n-- > 0)
		*to++ = '\0';

	return start;
}
```

### `strncat`

We use a similar approach as for `strncpy`:
```c
char *my_strncat(char *to, char const *from, int n)
{
	char *const start = to;

	while (*to != '\0') /* get the end of `to` */
		++to;
	while (n-- > 0 && (*to = *from) != '\0')
		to++, from++;
	*to = '\0';

	return start;
}
```

### `strncmp`

We slightly alter the implementation of `strncmp` from page 106:
```c
int my_strncmp(char const *s, char const *t, int n)
{
	for (; n > 0 && *s == *t; --n, ++s, ++t)
		if (*s == '\0')
			/* we reached the end of s and t without finding a difference */
			return 0;
	if (n <= 0)
		return 0;
	else
		return *s - *t;
}
```



## Testing

We use an auxiliary function `printArray` to print the complete content of a `char[]` as integers:
```c
void printArray(char arr[], int size)
{
	printf("[");
	for (int i = 0; i < size; ++i)
		printf("%d%c", arr[i], ' ');
	printf("]\n");
}
```

### `strncpy`

We test the function `strncpy` as follows:
```c
printf("STRNCPY\n");
char s1[] = "aaaaaaaaaa"; /* 10 a’s */
char t1[] = "bcd";
printf("target:\t");
printArray(s1, 11);
printf("source:\t");
printArray(t1, 4);
for (int n = 0; n <= 11; ++n) {
	char s1[] = "aaaaaaaaaa";
	printf("n = %d:\t", n);
	my_strncpy(s1, t1, n);
	printArray(s1, 11);
}
```
The output is as desired:
```text
STRNCPY
target:	[97 97 97 97 97 97 97 97 97 97 0 ]
source:	[98 99 100 0 ]
n = 0:	[97 97 97 97 97 97 97 97 97 97 0 ]
n = 1:	[98 97 97 97 97 97 97 97 97 97 0 ]
n = 2:	[98 99 97 97 97 97 97 97 97 97 0 ]
n = 3:	[98 99 100 97 97 97 97 97 97 97 0 ]
n = 4:	[98 99 100 0 97 97 97 97 97 97 0 ]
n = 5:	[98 99 100 0 0 97 97 97 97 97 0 ]
n = 6:	[98 99 100 0 0 0 97 97 97 97 0 ]
n = 7:	[98 99 100 0 0 0 0 97 97 97 0 ]
n = 8:	[98 99 100 0 0 0 0 0 97 97 0 ]
n = 9:	[98 99 100 0 0 0 0 0 0 97 0 ]
n = 10:	[98 99 100 0 0 0 0 0 0 0 0 ]
n = 11:	[98 99 100 0 0 0 0 0 0 0 0 ]
```

### `strncat`

We test the function `strncat` as follows:
```c
printf("\n\n");
printf("STRNCAT\n");
char s2[] = {'a', 'b', 'c', '\0', '\0', '\0', 'g', 'h', 'i', 'j', 'k'};
char t2[] = "def";
printf("target:\t");
printArray(s2, 11);
printf("source:\t");
printArray(t2, 4);
for (int n = 0; n <= 6; ++n) {
	char s2[] = {'a', 'b', 'c', '\0', '\0', '\0', 'g', 'h', 'i', 'j', 'k'};
	printf("n = %d:\t", n);
	my_strncat(s2, t2, n);
	printArray(s2, 11);
}
```
The output is as desired:
```text
STRNCAT
target:	[97 98 99 0 0 0 103 104 105 106 107 ]
source:	[100 101 102 0 ]
n = 0:	[97 98 99 0 0 0 103 104 105 106 107 ]
n = 1:	[97 98 99 100 0 0 103 104 105 106 107 ]
n = 2:	[97 98 99 100 101 0 103 104 105 106 107 ]
n = 3:	[97 98 99 100 101 102 0 104 105 106 107 ]
n = 4:	[97 98 99 100 101 102 0 104 105 106 107 ]
n = 5:	[97 98 99 100 101 102 0 104 105 106 107 ]
n = 6:	[97 98 99 100 101 102 0 104 105 106 107 ]
```

### `strncmp`

We test the function `strncmp` as follows:
```c
printf("\n\n");
printf("STRNCMP\n");
char *s = "abc";
char *t = "abcdef";
char *u = "abcddd";
printf("s:\t\"%s\"\n", s);
printf("t:\t\"%s\"\n", t);
printf("u:\t\"%s\"\n", u);

printf("\n");
for (int n = 0; n < 4; ++n)
	printf("s, s, n = %d\t%d\n", n, my_strncmp(s, s, n));
printf("\n");
for (int n = 0; n < 7; ++n)
	printf("s, t, n = %d\t%d\n", n, my_strncmp(s, t, n));
printf("\n");
for (int n = 0; n < 7; ++n)
	printf("t, u, n = %d\t%d\n", n, my_strncmp(t, u, n));
```
The output is as desired:
```text
STRNCMP
s:	"abc"
t:	"abcdef"
u:	"abcddd"

s, s, n = 0	0
s, s, n = 1	0
s, s, n = 2	0
s, s, n = 3	0

s, t, n = 0	0
s, t, n = 1	0
s, t, n = 2	0
s, t, n = 3	0
s, t, n = 4	-100
s, t, n = 5	-100
s, t, n = 6	-100

t, u, n = 0	0
t, u, n = 1	0
t, u, n = 2	0
t, u, n = 3	0
t, u, n = 4	0
t, u, n = 5	1
t, u, n = 6	1
```

# Exercise 2-3

> Write a function `htoi(s)`, which converts a string of hexadecimal digits (including an optional `0x` or `0X`) into its equivalent integer value.
> The allowable digits are `0` through `9`, `a` through `f`, and `A` through `F`.

---

We use auxiliary functions to determine whether a character is an allowed digit, and to compute its numerical value.
```c
bool ishexdigit(char c)
{
	return ('0' <= c && c <= '9') || ('a' <= c && c <= 'f') ||
	       ('A' <= c && c <= 'F');
}

int hexvalue(char c)
{
	if ('0' <= c && c <= '9')
		return c - '0';
	if ('a' <= c && c <= 'f')
		return c - 'a' + 10;
	if ('A' <= c && c <= 'F')
		return c - 'A' + 10;
	return -1;
}
```
We can then write the function `htoi` as follows:
```c
int htoi(const char s[])
{
	int result = 0;
	int sign = 1;

	int i = 0;

	/* Gobble up leading whitespace. */
	while (s[i] == ' ')
		++i;
	/* Determine the sign. */
	if (s[i] == '-') {
		sign = -1;
		++i;
	}
	/* Gobble up whitespace again. */
	while (s[i] == ' ')
		++i;
	/* Ignore optional 0x or 0X. */
	if (s[i] == '0' && (s[i + 1] == 'x' || s[i + 1] == 'X'))
		i += 2;
	/* Convert the remaining digits. */
	for (; ishexdigit(s[i]); ++i) {
		result *= 16;
		result += hexvalue(s[i]);
	}
	/* Finally, return the result. */
	return sign * result;
}
```

We can test our function with the following code:
```c
const char *strings[24] = {"1f",     "1F",    "0x1f",    "0X1F",   " 1f",
                           " 1F",    " 0x1f", " 0X1F",   "-1f",    "-1F",
                           "-0x1f",  "-0X1F", " -1f",    " -1F",   " -0x1f",
                           " -0X1F", "- 1f",  "- 1F",    "- 0x1f", "- 0X1F",
                           " - 1f",  " - 1F", " - 0x1f", " - 0X1F"};
for (int i = 0; i < 24; ++i)
	printf("\"%s\" \t %d\n", strings[i], htoi(strings[i]));
return 0;
```
The results are as desired:
```text
"1f" 	31
"1F" 	31
"0x1f" 	31
"0X1F" 	31
" 1f" 	31
" 1F" 	31
" 0x1f" 	31
" 0X1F" 	31
"-1f" 	-31
"-1F" 	-31
"-0x1f" 	-31
"-0X1F" 	-31
" -1f" 	-31
" -1F" 	-31
" -0x1f" 	-31
" -0X1F" 	-31
"- 1f" 	-31
"- 1F" 	-31
"- 0x1f" 	-31
"- 0X1F" 	-31
" - 1f" 	-31
" - 1F" 	-31
" - 0x1f" 	-31
" - 0X1F" 	-31
```

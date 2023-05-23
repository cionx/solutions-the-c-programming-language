# Exercise 2-3

> Write a function `htoi(s)`, which converts a string of hexadecimal digits (including an optional `0x` or `0X`) into its equivalent integer value.
> The allowable digits are `0` through `9`, `a` through `f`, and `A` through `F`.



We decide to interpret the empty string as the empty sum, which has value `0`.
```c
int htoi(char s[])
{
	/* We regard the occurrence of no digits as the empty sum. */
	if (s[0] == '\0')
		return 0;
```
Otherwise, we will need an index to go through the input string.
```c
	int i = 0;
```
We allow for leading whitespace.
```c
	/* Ignore leading whitespace. */
	while (whitespace(s[i]))
		++i;
```
We also support negative numbers.
The minus sign must be placed before the optional `0x`/`0X`.
```c
	/* Support negative numbers. */
	bool negative = false;
	if ((negative = (s[i] == '-')))
		++i;
```
We do, however, support whitespace between the minus sign and `0x`/`0X`.
```c
	/* Ignore whitespace between minus sign and 0x/0X. */
	while (whitespace(s[i]))
		++i;
```
We simply skip the leading `0x`/`0X` if present.
```c
	if (hexa_start(s, i))
		i += 2;
```
Finally, the core computation.
The auxiliary function `hexa_value` actually checks if its input is a valid hexademical digits (and returns `-1` if so).
But we don’t seem to have a way to make `htoi` return an error (because we also allow negative values), so we ignore this check in our core computation.
```c
	int sum = 0;
	for (; s[i] != '\0'; i++) {
		sum *= 16;
		sum += hexa_value(s[i]);
	}
```
Before returning the final value we have to remember if the result is supposed to be negative.
```c
	if (negative)
		return -sum;
	else
		return sum;
}
```

The auxiliary functions are as follows:
```c
/* Checks if a character is inline whitespace. */
bool whitespace(char c)
{
	return c == ' ' || c == '\t';
}

/* Checks for 0x/0X at the given position. */
bool hexa_start(char s[], int i)
{
	return (s[i] == '0') && (s[i + 1] == 'x' || s[i + 1] == 'X');
}

/* The character needs to be a valid hexadecimal digit.
 * Otherwise, -1 is returned.
 */
int hexa_value(char c)
{
	if ('0' <= c && c <= '9')
		return c - '0';
	else if ('a' <= c && c <= 'f')
		return 10 + c - 'a';
	else if ('A' <= c && c <= 'F')
		return 10 + c - 'A';

	return -1;
}
```

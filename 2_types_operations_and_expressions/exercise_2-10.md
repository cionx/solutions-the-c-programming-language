# Exercise 2-10

> Rewrite the function `lower`, which converts upper case letters to lower case, with a conditional expression instead of `if`-`else`.



The original code for `lower` is given on page 43 as follows:
```c
int lower(int c)
{
	if (c >= 'A' && c <= 'Z')
		return c + 'a' - 'A';
	else
		return c;
}
```
We can simply replace the `if`-`else` by a conditional expression:
```c
int lower(char c)
{
	return ('A' <= c && c <= 'Z') ? c + 'a' - 'A' : c;
}
```

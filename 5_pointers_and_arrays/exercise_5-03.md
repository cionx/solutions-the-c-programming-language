# Exercise 5-3

> Write a pointer version of the function `strcat` that we showed in Chapter 2:
> `strcat(s,t)` copies the string `t` to the end of `s`.

---

We can implement the described function as follows:
```c
/* strcat(s, t): appends t to s */
void strcat(char *s, const char *t)
{
	while (*s != '\0')
		++s;
	while ((*s = *t) != '\0')
		++s, ++t;
}
```

We test our function as follows:
```c
int main(void)
{
	char s[10] = "abc";
	char t[] = "def";

	printf("s = \"%s\", t = \"%s\"", s, t);
	strcat(s, t);
	printf(" becomes \"%s\"\n", s);

	return 0;
}
```
The output is as desired:
```text
s = "abc", t = "def" becomes "abcdef"
```

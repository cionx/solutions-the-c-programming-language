# Exercise 4-7

> Write a routine `ungets(s)` that will push back an entire string onto the input.
> Should `ungets` know about `buf` and `bufp`, or should it just use `ungetch`? □

---

We will implement `ungets` in terms of `ungetch`.
A string is just an array of characters (that is zero-terminated), so we can simply iterate over the array and apply `ungetch` to each character.
There is, however, a slight problem here:
in which direction should we iterate over the array?
We cannot answer this question without further context, or specific use cases of `ungets`.

We will iterate over the array in opposite direction.
This has the effect that `getch` will later read off these characters in the same order that they were presented in the input string `s`:
```text
buffer    string
a b c     def

       ↓ ungets

buffer
a b c f e d

       ↓ read off 3 characters

buffer    characters
a b c     d e f
```

We arrive at the following code:
```c
void ungets(char s[])
{
	int i = 0;
	/* Search for the last character */
	while (s[i] != 0)
		++i;
	--i;

	for (; i >= 0; --i)
		ungetch(s[i]);
}
```
(We have not tested this function.)

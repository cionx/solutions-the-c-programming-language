# Exercise 2-7

> Write a function `invert(x,p,n)` that returns `x` with the `n` bits that begin at position `p` inverted (i.e., 1 changed into 0 and vice versa), leaving the others unchanged.

---

We create a `mask` that consists of `n` many 1s starting at position `p`:
```c
unsigned int mask = ~(~0u << n)
                    << (p - n + 1); // n 1s at position p, rest 0
```
We then combine this mask with `x` via `^`:
```c
unsigned int invert(unsigned int x, int p, int n)
{
	if (n > p)
		n = p + 1;
	unsigned int mask = ~(~0u << n)
	                    << (p - n + 1); // n 1s at position p, rest 0
	return x ^ mask;
}
```

We can test our function with the following example:
```c
unsigned int x = 255;              // …011111111
unsigned result = invert(x, 5, 3); // …011000111 = 199
printf("%d\n", result);
```

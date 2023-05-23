# Exercise 2-7

> Write a function `invert(x,p,n)` that returns `x` with the `n` bits that begin at position `p` inverted (i.e., 1 changed into 0 and vice versa), leaving the others unchanged.



We can proceed as in the last exercise, except that this time, we combine `x` with the `mask` via exclusive or.
```c
unsigned int invert(unsigned int x, int p, int n)
{
	if (n > p)
		n = p + 1;
	unsigned int mask = ~(~0u << n) << (p - n + 1); // n 1s at position p, rest 0
	return x^mask;
}
```

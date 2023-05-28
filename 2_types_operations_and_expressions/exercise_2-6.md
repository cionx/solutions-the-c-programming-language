# Exercise 2-6

> Write a function `setbits(x,p,n,y)` that returns `x` with the `n` bits that begin at position `p` set to the rightmost `n` bits of `y`, leaving the other bits unchanged.



The maximal sensible value for `n` is `p + 1`.
We therefore trim `n` to this maximal value:
```c
if (n > p)
	n = p + 1;
```
To solve the problem, we create a `mask` that has a block of ones of length `n` starting at position `p`, and is zero everywhere else.
```c
unsigned int mask = ~(~0u << n) << (p - n + 1); // n 1s at position p, rest 0
```
(Note that we use `0u` instead of simply `0` to avoid an implicit type cast from `int` to `unsigned int`.)
We use this mask to set the respective part of `x` to all zeros, cut out the respective part in `y`, and then merge both pieces:
```c
return (x & ~mask) | (y & mask);
```

We get overall the following function:
```c
unsigned int setbits(unsigned int x, int p, int n, unsigned int y)
{
	if (n > p)
		n = p + 1;
	unsigned int mask = ~(~0 << n) << (p - n + 1); // n 1s at position p, rest 0
	return (x & ~mask) | (y & mask);
}
```

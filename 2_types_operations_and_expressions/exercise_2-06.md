# Exercise 2-6

> Write a function `setbits(x,p,n,y)` that returns `x` with the `n` bits that begin at position `p` set to the rightmost `n` bits of `y`, leaving the other bits unchanged.

---

The maximal sensible value for `n` is `p + 1`.
We therefore trim `n` to this maximal value:
```c
if (n > p)
	n = p + 1;
```
We first create a right-aligned block of `n` many `1`s:
```c
unsigned int ones = ~(~0u << n); // Right-aligned block of n many 1s.
```
We then remove from `x` the `n` bits starting at position `p`, i.e., we set them to zero:
(To get the shifting right note that in the case $n = p + 1$ the shift is zero.)
```c
unsigned int x_removed = x & ~(ones << (p + 1 - n));
```
We now extract the rightmost `n` bits of `y`:
```c
unsigned int y_rightmost = y & ones;
```
Finally, we move this rightmost block at the correct position and insert it into `x_removed`:
```c
return x_removed | (y_rightmost << (p + 1 - n));
```

We get overall the following function:
```c
unsigned int setbits(unsigned int x, int p, int n, unsigned int y)
{
	if (n > p)
		n = p + 1;
	unsigned int ones = ~(~0u << n); // Right-aligned block of n many 1s.
	unsigned int x_removed = x & ~(ones << (p + 1 - n));
	unsigned int y_rightmost = y & ones;
	return x_removed | (y_rightmost << (p + 1 - n));
}
```
We can test our code with the following example, with $p = 6$ and $n = 5$:
```text
          position        value
          876543210

            _____
x         011110000       240

              _____
y         000001111        15

            _____
result    010111100       188
```
In code:
```c
unsigned int x = 240;                // …011110000
unsigned int y = 15;                 // …000001111
printf("%u\n", setbits(x, 6, 5, y)); // …010111100 = 188
```

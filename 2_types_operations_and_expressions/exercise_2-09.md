# Exercise 2-9

> In a two’s complement number system, `x &= (x - 1)` deletes the rightmost `1`-bit in `x`.
> Explain why.
> Use this observation to write a faster version of `bitcount`.

---

The given statement is true if `x` is nonzero.
(For zero, the given procedure results again in zero.)
The number `x` is then of the following form:
```text
b₁ … bₙ 1 0 0 … 0 0
```
Subtracting 1 gives the following number.
```text
b₁ … bₙ 0 1 1 … 1 1
```
The number `x & (x - 1)` looks therefore as follows:
```
b₁ … bₙ 0 0 0 … 0 0
```
We see that the right-most `1` has been deleted, while all other bits remain unchanged.

We can now write the following version of `bitbcount`:
```c
int faster_bitcount(unsigned int x)
{
	int b = 0;
	while (x != 0) {
		x &= (x - 1);
		++b;
	}

	return b;
}
```

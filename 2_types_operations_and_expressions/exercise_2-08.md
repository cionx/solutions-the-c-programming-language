# Exercise 2-8

> Write a function `rightrot(x, n)` that returns the value of the integer `x` rotated to the right by `n` bit positions.

---

If the size of `unsigned int` is `k` bits, then rotating `k` times results in the original `x`.
We can therefore reduce `n` modulo `k` to prevent unnecessary rotations.
To this end, we need to find out `k`.
The value can be found in `limits.h` as `UINT_WIDTH`, but for some reason, this macro doesn’t seem to be properly exported.
We therefore use the (not-yet introduced) `sizeof` operator to determine this `width`:
```c
unsigned int rightrot(unsigned int x, int n)
{
	int width = 8 * sizeof(unsigned int);
	// UINT_WIDTH from limits.h doesn't work for some reason.
	n %= width;
```
We want to split `x` into two parts: the first `n` bits from the right, which we shall call the `tail`, and the rest of `n`, which we shall call the `head`.
We need to swap the positions of `head` and `tail`.
This can be done by shifting the head `n` places to the right, and the tail `width - n` places to the left.
```c
	unsigned int mask = ~(~0u << n); // n many 1's right-adjusted
	unsigned int head = x & ~mask;
	unsigned int tail = x & mask;
	return (head >> n) | (tail << (width - n));
}
```

We test our function by rotating `1` for every sensible value of `n`:
```c
unsigned int x = 1;
int width = 8 * sizeof(unsigned int);
for (int i = 0; i <= width; ++i)
	printf("%2d  %u\n", i, rightrot(x, i));
```
The result is as desired:
```text
 0  1
 1  2147483648
 2  1073741824
 3  536870912
 4  268435456
 5  134217728
 6  67108864
 7  33554432
 8  16777216
 9  8388608
10  4194304
11  2097152
12  1048576
13  524288
14  262144
15  131072
16  65536
17  32768
18  16384
19  8192
20  4096
21  2048
22  1024
23  512
24  256
25  128
26  64
27  32
28  16
29  8
30  4
31  2
32  1
```

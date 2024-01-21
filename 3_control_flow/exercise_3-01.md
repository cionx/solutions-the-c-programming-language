# Exercise 3-1

> Our binary search makes two tests inside the loop, when one would suffice (at the price of more tests outside).
> Write a version with only one test inside the loop and measure the difference in run time.

---

We could rewrite `binsearch` as follows:
```c
int binsearch_new(int x, int v[], int vsize)
{
	int low, high, mid;
	low = 0;
	high = vsize - 1;
	while (low < high) {
		mid = (low + high) / 2; /* always lower that high */
		if (x > v[mid])
			low = mid + 1;      /* strictly increases low */
		else
			high = mid;         /* strictly decreases high */
	}
	return (v[low] == x) ? low : -1;
}
```

To time the two functions we create an array containing all integers from 0 to 99, and then search for each of these integers inside the array.
We do this 10 million times.
```c
int main(void)
{
	int v[] = {0,  1,  2,  3,  4,  5,  6,  7,  8,  9,  10, 11, 12, 14, 15,
	           16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30,
	           31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45,
	           46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 58, 59, 60, 70,
	           71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85,
	           86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99};

	int repeat = 1e7;
	for (int i = 0; i < repeat; ++i)
		for (int x = 0; x < 100; ++x)
			binsearch(x, v, 100);

	return 0;
}
```

The original `binsearch` takes roughly 121 seconds.
```text
$ clang exercise_3-01.c && date && ./a.out && date
Mon 29 May 15:48:56 CEST 2023
Mon 29 May 15:48:57 CEST 2023
```
The new `binsearch_new` takes around 136 seconds.
```text
$ clang exercise_3-01.c && date && ./a.out && date
Mon 29 May 15:51:31 CEST 2023
Mon 29 May 15:53:47 CEST 2023
```
Our new version seems to be slightly worse than the old version.
We guess this is due to the fact that the old version can terminate the loop once it has found the given value, whereas our version has to continue until it has shrunk the interval under consideration down to a single value.

# Exercise 4-12

> Adapt the ideas of `printd` to write a recursive version of `itoa`;
> that is, convert an integer into a string by calling a recursive routine.

---

We use an approach similar to Exercise 3-4 to support all integers, including `INT_MIN`.
```c
#include <limits.h>
#include <stdio.h>

void itoa(int n, char s[]);
int helper(int n, char s[]);

void itoa(int n, char s[])
{
	/* Handle this special case by hand. */
	if (n == 0) {
		s[0] = '0';
		s[1] = '\0';
	}

	/* Make n negative and set the sign. */
	int i = 0;
	if (n < 0)
		s[i++] = '-';
	else
		n = -n;

	helper(n, s + i);       /* pointer arithmetic */
}

int helper(int n, char s[]) /* returns the length of the computed string. */
{
	if (n == 0) {
		return 0;
	}
	char digit = -(n % 10) + '0';
	int pos = helper(n / 10, s);
	s[pos] = digit;
	s[pos + 1] = '\0';
	return pos + 1;
}
```

We can test our function as follows:
```c
int main(void)
{
	int nums[] = {0, 123, -123, INT_MAX, INT_MIN};
	char s[100];
	for (int i = 0; i < 5; ++i) {
		itoa(nums[i], s);
		printf("%d becomes \"%s\"\n", nums[i], s);
	}
	return 0;
}
```
The output is as desired:
```text
0 becomes "0"
123 becomes "123"
-123 becomes "-123"
2147483647 becomes "2147483647"
-2147483648 becomes "-2147483648"
```

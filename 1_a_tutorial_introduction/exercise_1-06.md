# Exercise 1-6

> Verify that the expression `getchar() != EOF` is 0 or 1.

---

We use the following code:
```c
#include <stdio.h>

int main(void)
{
	int c = 'a'; /* An initial value that is not EOF. */
	while (c != EOF) {
		c = getchar();
		printf("The character %d gives %d\n", c, c != EOF);
	}
}
```
The compiled program has the following behaviour:

- With Ctrl+C, the program exits.

- With Ctrl+D, the program prints `0` and then exits.

- With every ASCII character that we tested, the program prints two `1`s.
  This makes sense:
  after inputing the character itself, we also press the enter key.
  This will give `getchar()` two characters:
  the character itself, and the newline character `\n` coming from pressing the enter key.

Our program seems to support the claim that `getchar() != EOF` is always 0 or 1.

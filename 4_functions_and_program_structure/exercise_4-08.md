# Exercise 4-8

> Suppose that there will never be more than one character of pushback.
> Modify `getch` and `ungetch` accordingly.

---

We can rewrite the buffer as follows:
```c
/* BUFFER */

#include <stdbool.h>

char buffer;    /* buffer for ungetch */
bool buffered;

int getch(void) /* get a (possibly pushed back) character */
{
	if (buffered) {
		buffered = false;
		return buffer;
	}
  else
		return getchar();
}

void ungetch(int c) /* push character back on input */
{
	buffer = c;
}
```

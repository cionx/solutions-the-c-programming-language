# Exercise 4-14

> Define a macro `swap(t,x,y)` that interchanges two arguments of type `t`.
> (Block structure will help.)

---

We can write the described macro as follows:
```c
#define swap(t, x, y)  {t tmp = x; x = y; y = tmp;}
```

We test this macro as follows:
```c
#include <stdio.h>

#define swap(t, x, y)  {t tmp = x; x = y; y = tmp;}

int main(void)
{
	int x = 1;
	int y = 2;
	printf("Before: x = %d, y = %d.\n", x, y);
	swap(int, x, y)
	printf("After:  x = %d, y = %d.\n", x, y);
}
```
The output is as desired:
```text
Before: x = 1, y = 2.
After:  x = 2, y = 1.
```

# Exercise 1-7

> Write a program to print the value of `EOF`.

---

The book states the following:

> `EOF` is an integer defined in `<stdio.h>` […].

As `EOF` is an integer, we can print its value using `printf`:
```c
#include <stdio.h>

int main(void)
{
	printf("%d\n", EOF);
}
```
We find that the value of `EOF` is -1:
```text
$ ./a.out
-1
```

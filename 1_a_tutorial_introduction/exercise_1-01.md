# Exercise 1-1

> Run the “`hello, world`” program on your system.
> Experiment with leaving out parts of the program, to see what error messages you get.

---

The complete code for the “`hello world`” program is as follows:
```c
#include <stdio.h>

int main(void)
{
	printf("hello, world\n");
}
```

- If we leave out the header `#include <stdio.h>`, we get the following warning during compilation:
  ```text
  hello.c:4:2: warning: call to undeclared library function 'printf' with type 'int (const char *, ...)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
          printf("hello, world");
          ^
  hello.c:4:2: note: include the header <stdio.h> or explicitly provide a declaration for 'printf'
  1 warning generated.
  ```
  But we still get an executable `a.out` that provides the same output as the original program.

- If we leave out the type `int` in the declaration `int main(void)`, we get the following warning during compilation:
  ```text
  hello.c:3:1: warning: type specifier missing, defaults to 'int'; ISO C99 and later do not support implicit int [-Wimplicit-int]
  main(void)
  ^
  int
  1 warning generated.
  ```
  But we still get an executable `a.out` that provides the same output as the original program.

- If we leave out the parenthesized part of `main(void)`, then we get the following warning and error during compilation:
  ```text
  hello.c:3:1: warning: variable named 'main' with external linkage has undefined behavior [-Wmain]
  int main
  ^
  hello.c:3:9: error: expected ';' after top level declarator
  int main
          ^
          ;
  1 warning and 1 error generated.
  ```
  This time we get no executable.

- If we leave out the semicolon in `printf("hello, world\n");`, then we get the following error during compilation:
  ```text
  hello.c:5:26: error: expected ';' after expression
          printf("hello, world\n")
                                  ^
                                  ;
  1 error generated.
  ```
  We once again get no executable.

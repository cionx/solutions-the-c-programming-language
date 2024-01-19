# Exercise 1-2

> Experiment to find out what happens when `printf`’s argument contains `\c` where `c` is some constant not listed above.

---

We use the following code:
```c
#include <stdio.h>

int main(void)
{
	printf("The letter \a a\n");
	printf("The letter \c c\n");
	printf("The letter \d d\n");
	printf("The letter \e e\n");
	printf("The letter \f f\n");
	printf("The letter \g g\n");
	printf("The letter \h h\n");
	printf("The letter \i i\n");
	printf("The letter \j j\n");
	printf("The letter \k k\n");
	printf("The letter \l l\n");
	printf("The letter \m m\n");
	printf("The letter \o o\n");
	printf("The letter \p p\n");
	printf("The letter \q q\n");
	printf("The letter \r r\n");
	printf("The letter \s s\n");
	printf("The letter \t t\n");
	printf("The letter \u u\n");
	printf("The letter \v v\n");
	printf("The letter \w w\n");
	printf("The letter \x x\n");
	printf("The letter \y y\n");
	printf("The letter \z z\n");
	printf("The symbol \. .\n");
	printf("The symbol \, ,\n");
	printf("The symbol \; ;\n");
	printf("The symbol \? ?\n");
	printf("The symbol \! !\n");
	printf("The symbol \/ /\n");
}
```
We get the following messaged from the compiler:
```text
exercise_1-02.c:6:21: warning: unknown escape sequence '\c' [-Wunknown-escape-sequence]
        printf("The letter \c c\n");
                           ^~
exercise_1-02.c:7:21: warning: unknown escape sequence '\d' [-Wunknown-escape-sequence]
        printf("The letter \d d\n");
                           ^~
exercise_1-02.c:10:21: warning: unknown escape sequence '\g' [-Wunknown-escape-sequence]
        printf("The letter \g g\n");
                           ^~
exercise_1-02.c:11:21: warning: unknown escape sequence '\h' [-Wunknown-escape-sequence]
        printf("The letter \h h\n");
                           ^~
exercise_1-02.c:12:21: warning: unknown escape sequence '\i' [-Wunknown-escape-sequence]
        printf("The letter \i i\n");
                           ^~
exercise_1-02.c:13:21: warning: unknown escape sequence '\j' [-Wunknown-escape-sequence]
        printf("The letter \j j\n");
                           ^~
exercise_1-02.c:14:21: warning: unknown escape sequence '\k' [-Wunknown-escape-sequence]
        printf("The letter \k k\n");
                           ^~
exercise_1-02.c:15:21: warning: unknown escape sequence '\l' [-Wunknown-escape-sequence]
        printf("The letter \l l\n");
                           ^~
exercise_1-02.c:16:21: warning: unknown escape sequence '\m' [-Wunknown-escape-sequence]
        printf("The letter \m m\n");
                           ^~
exercise_1-02.c:17:21: error: expected '{' after '\o' escape sequence
        printf("The letter \o o\n");
                           ^~
exercise_1-02.c:18:21: warning: unknown escape sequence '\p' [-Wunknown-escape-sequence]
        printf("The letter \p p\n");
                           ^~
exercise_1-02.c:19:21: warning: unknown escape sequence '\q' [-Wunknown-escape-sequence]
        printf("The letter \q q\n");
                           ^~
exercise_1-02.c:21:21: warning: unknown escape sequence '\s' [-Wunknown-escape-sequence]
        printf("The letter \s s\n");
                           ^~
exercise_1-02.c:23:21: error: \u used with no following hex digits
        printf("The letter \u u\n");
                           ^~
exercise_1-02.c:25:21: warning: unknown escape sequence '\w' [-Wunknown-escape-sequence]
        printf("The letter \w w\n");
                           ^~
exercise_1-02.c:26:21: error: \x used with no following hex digits
        printf("The letter \x x\n");
                           ^~
exercise_1-02.c:26:21: warning: format string contains '\0' within the string body [-Wformat]
        printf("The letter \x x\n");
               ~~~~~~~~~~~~^~~~~~~
exercise_1-02.c:27:21: warning: unknown escape sequence '\y' [-Wunknown-escape-sequence]
        printf("The letter \y y\n");
                           ^~
exercise_1-02.c:28:21: warning: unknown escape sequence '\z' [-Wunknown-escape-sequence]
        printf("The letter \z z\n");
                           ^~
exercise_1-02.c:29:21: warning: unknown escape sequence '\.' [-Wunknown-escape-sequence]
        printf("The symbol \. .\n");
                           ^~
exercise_1-02.c:30:21: warning: unknown escape sequence '\,' [-Wunknown-escape-sequence]
        printf("The symbol \, ,\n");
                           ^~
exercise_1-02.c:31:21: warning: unknown escape sequence '\;' [-Wunknown-escape-sequence]
        printf("The symbol \; ;\n");
                           ^~
exercise_1-02.c:33:21: warning: unknown escape sequence '\!' [-Wunknown-escape-sequence]
        printf("The symbol \! !\n");
                           ^~
exercise_1-02.c:34:21: warning: unknown escape sequence '\/' [-Wunknown-escape-sequence]
        printf("The symbol \/ /\n");
                           ^~
21 warnings and 3 errors generated.
```

The new escape sequences are `\a`, `\e`, `\f`, `\o`, `\r`, `\u`, `\v`, `\x` and `\?`.
For every other escape sequence we get a warning.

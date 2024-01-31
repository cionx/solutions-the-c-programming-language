# Exercise 5-11

> Modify the programs `entab` and `detab` (written as exercises in Chapter 1) to accept a list of tab stops as arguments.
> Use the default tab settings if there are no arguments.

---

### `detab`

We have already written `detab` so that the tab length is configurable.
Here’s our previous code:
```c
#include <stdio.h>

#define MAXLINE  1000
#define LENERROR -1
#define TABSIZE  4

int detab(char s[], int tabsize);
int getaline(char line[], int lim);

int main(void)
{
	char line[MAXLINE];
	int code = 0;

	while (getaline(line, MAXLINE) > 0) {
		if ((code = detab(line, TABSIZE)) < 0)
			return code;
		printf("%s", line);
	}

	return 0;
}

int detab(char line[], int tabsize)
{
	⋮
}

int getaline(char s[], int lim)
{
	⋮
}
```

We want to make the tab length configurable via the flag `-t <length>`.
This leads to the following modified main function:
```c
⋮
#define DFLT_TABLEN 4 /* default tab lenght */
⋮

int main(int argc, char *argv[])
{
	char line[MAXLINE];
	int code = 0;
	int tablen = DFLT_TABLEN;

	if (argc >= 2) {
		char *flag = argv[1];
		if (strcmp(flag, "-t") != 0) {
			printf("detab: unknown option %s\n", flag);
			return -1;
		}
		if (argc < 3) {
			printf("detab: missing tab length\n");
			return -1;
		}
		char *argument = argv[2];
		tablen = atoi(argument);
	}

	while (getaline(line, MAXLINE) > 0) {
		if ((code = detab(line, tablen)) < 0)
			return code;
		printf("%s", line);
	}

	return 0;
}

⋮
```

We tested this program with the following terminal code, with `<number>` from zero to five:
```sh
$ cat detab.c | ./a.out
$ cat detab.c | ./a.out -l
$ cat detab.c | ./a.out -t
$ cat detab.c | ./a.out -t <number>
```



### `entab`

We also have written `entab` to have a configurable tab length.
Our previous code looked as follows:
```c
#include <stdio.h>

#define MAXLEN 100000
#define TABLEN 4

void entab(char s[], int tablen);
int getaline(char line[], int lim);

int main(void)
{
	char line[MAXLEN];

	while (getaline(line, MAXLEN) > 0) {
		entab(line, TABLEN);
		printf("%s", line);
	}

	return 0;
}

/* Replaces leading blanks by the equivalent amount of tabs and blanks.
 * The tab length must be positive. */
void entab(char s[], int tablen)
{
	⋮
}

int getaline(char s[], int lim)
{
	⋮
}
```

We can use the same additional code as for `detab` to make the tab length configurable via the flag `-t <length>`:
```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLEN      100000
#define DFLT_TABLEN 4

void entab(char s[], int tablen);
int getaline(char line[], int lim);

int main(int argc, char *argv[])
{
	char line[MAXLEN];
	int tablen = DFLT_TABLEN;

	if (argc >= 2) {
		char *flag = argv[1];
		if (strcmp(flag, "-t") != 0) {
			printf("entab: unknown option %s\n", flag);
			return -1;
		}
		if (argc < 3) {
			printf("entab: missing tab length\n");
			return -1;
		}
		char *argument = argv[2];
		tablen = atoi(argument);
	}

	while (getaline(line, MAXLEN) > 0) {
		entab(line, tablen);
		printf("%s", line);
	}

	return 0;
}
```

We used the same test text as for Exercise 1-21:
```text
0 leading spaces
 1 leading spaces
  2 leading spaces
   3 leading spaces
    4 leading spaces
     5 leading spaces
      6 leading spaces
       7 leading spaces
        8 leading spaces
         9 leading spaces
          10 leading spaces
           11 leading spaces
            12 leading spaces
```

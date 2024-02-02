# Exercise 5-14

> Modify the sort program to handle a `-r` flag, which indicates sorting in reverse (decreasing) order.
> Be sure that `-r` works with `-n`.

---

We first sort the lines as usual, and then reverse the result if so required.
Our modified `main` function looks as follows:
```c
int main(int argc, char *argv[])
{
	int nlines;            /* number of input lines read */
	bool numeric = false;  /* true if numeric sort */
	bool reversed = false; /* true if reverse sort */

	/* Read the flags. */
	while (--argc > 0) {
		char *arg = *++argv;
		if (arg[0] != '-') {
			printf("Unknown option: %s\n", arg);
			return 1;
		}
		for (int i = 1; arg[i] != '\0'; ++i) {
			switch (arg[i]) {
				case 'n':
					numeric = true;
					break;
				case 'r':
					reversed = true;
					break;
				default:
					printf("Unknown flag: %c\n", arg[i]);
					return 1;
			}
		}
	}

	/* The actual sorting. */
	if ((nlines = readlines(lineptr, MAXLINES)) >= 0) {
		quicksort(
			(void **) lineptr, 0, nlines - 1,
			(int (*)(const void *, const void *))(numeric ? numcmp : strcmp));
		if (reversed) /* Reverse the result if requested. */
			reverse((void **) lineptr, 0, nlines - 1);
		writelines(lineptr, nlines);
		return 0;
	}
	else {
		printf("input too big to sort\n");
		return 1;
	}
}
```
The function `reverse` is implemented in terms of `swap`:
```c
void reverse(void *v[], int i, int j)
{
	for (; i < j; ++i, --j)
		swap(v, i, j);
}
```

We tested the overall program with the following test file:
```text
2
-1.5
3.5
-6
-4.5
```
We tested the flags `-n`, `-nr`, `-rn`, `-r` and no flags.
The result was correct in each case.

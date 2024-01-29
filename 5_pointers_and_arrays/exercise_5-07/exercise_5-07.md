# Exercise 5-7

> Rewrite `readlines` to store lines in an array supplied by `main,` rather than calling `alloc` to maintain storage.
> How much faster is the program?

---

We provide `readlines` with an additional argument:
an array of characters in which the lines will be saved one after another.
```c
int readlines(char *lineptr[], int nlines, char *storage);
```

In `main` we allocate an array of sufficient size and pass it to `readlines`:
```c
⋮
#define MAXLINES 5000           /* maximum number of lines to be sorted */
#define MAXLEN   1000           /* max length of any input line */
⋮
	⋮
	int nlines; /* number of input lines read */
	char storage[MAXLINES * MAXLEN];

	if ((nlines = readlines(lineptr, MAXLINES, storage)) >= 0) {
	⋮
```

In `readlines` we use the variable `storage` to keep track of the position at which unused space begins:
```c
/* readlines: read input lines */
int readlines(char *lineptr[], int maxlines, char *storage)
{
	int len, nlines;
	char line[MAXLEN];

	nlines = 0;
	while ((len = getaline(line, MAXLEN)) > 0) {
		if (nlines >= maxlines)
			return -1;
		else {
			line[len - 1] = '\0'; /* delete newline */
			strcpy(storage, line);
			lineptr[nlines++] = storage;
			storage += len;
		}
	}
	return nlines;
}
```
Note that `readlines` does not test if `storage` has enough space left;
this is `main`’s responsibility.

We are not sure how to measure the difference in speed, as both programs execute practically instantaneously on our machine.

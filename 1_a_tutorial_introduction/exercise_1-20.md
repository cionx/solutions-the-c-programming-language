# Exercise 1-20

> Write a program `detab` that replaces tabs in the input with the proper number of blanks to space to the next tab stop.
> Assume a fixed set of tab stops, say every _n_ columns.
> Should _n_ be a variable or a symbolic parameter.



We choose to make `n` an argument for `detab`, so that it can (in principle) be configured by the user of the program.
The default tabwidth of 4.

To detab a `line` we first construct the `result` in a new string, and afterwards overwrite `line` with `result`.

To construct the `result`, we go through `line` character by character.
While passing through the `line`, we _always_ keep track of how many spaces the current character were worth if it were a tab character.
For every character in the `line` we then have two cases two consider:
- If the character is not a tab character, then we simply copy it to the `result`, and adjust the space cost of the next character (mostly by decreasing the current cost by one).
- Otherwise, we add as many spaces to the `result` as the found tab character is cost.
  Afterwards we reset the space cost of the next character to the full tabwidth.

We hence have to keep track of two indices:
one index for the position in `line` that we are copying from, and one index for the position in `result` that we write to.
If no tab characters occur, then both indices stay equal.
But if a tab character occurs that is expanded to more than one space, then the writing index overtakes the reading index.

We also have to ensure that the detabed line does not exceed `MAXLINE` in length.
If it does, then the program stops and returns the value `-1`.

We get altogether the following code:
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
	char result[MAXLINE];
	int j;      /* Position in `result` to write to. */
	int spaces; /* How many spaces a tab at the current position is worth. */

	j = 0;
	spaces = tabsize;
	for (int i = 0; i < MAXLINE && line[i] != '\0' && j < MAXLINE; ++i) {
		/* Either expand a tab character... */
		if (line[i] == '\t') {
			for (; spaces > 0 && j < MAXLINE; --spaces, ++j)
				result[j] = ' ';
		}
		/* ... or just copy the current character. */
		else {
			result[j] = line[i];
			--spaces;
			++j;
		}
		if (spaces == 0)
			spaces = tabsize;
	}

	/* Check if the result fits into MAXLINE. More explicitly, check if there is
	 * enough space left to add \0. */
	if (j >= MAXLINE) {
		printf("Error: Not enough space to expand with tabwidth %d:\n\"%s\"",
		       tabsize, line);
		return LENERROR;
	}
	result[j] = '\0';

	/* Finally, copy the result back into `line`, including the trailing \0. */
	for (int i = 0; i <= j; ++i) {
		line[i] = result[i];
	}

	/* Return the length of the detabed line. */
	return j;
}

int getaline(char s[], int lim)
{
	int c, i;

	c = 0;
	for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; ++i)
		s[i] = (char) c;
	if (c == '\n') {
		s[i] = (char) c;
		++i;
	}
	s[i] = '\0';
	return i;
}
```

We consider the following example text, in which the words are indented and separated by tabs.
```text
	a	x
	bb	x
	ccc	x
	dddd	y
	eeeee	y
	ffffff	y
	ggggggg	y
```
We get the following results:
<table>
<tr>
<th> <code>tabwidth</code> </th>
<th> output </th>
</tr>
<tr>
<td> 4 </td>
<td>

```text
    a   x
    bb  x
    ccc x
    dddd    y
    eeeee   y
    ffffff  y
    ggggggg y
```

</td>
</tr>
<tr>
<td> 3 </td>
<td>

```text
   a  x
   bb x
   ccc   x
   dddd  y
   eeeee y
   ffffff   y
   ggggggg  y
```

</td>
</tr>
<tr>
<td> 2 </td>
<td>

```text
  a x
  bb  x
  ccc x
  dddd  y
  eeeee y
  ffffff  y
  ggggggg y
```

</td>
</tr>
<tr>
<td> 1 </td>
<td>

```text
 a x
 bb x
 ccc x
 dddd y
 eeeee y
 ffffff y
 ggggggg y
```

</td>
</tr>
<tr>
<td> 0 </td>
<td>

```text
ax
bbx
cccx
ddddy
eeeeey
ffffffy
gggggggy
```

</td>
</tr>
</table>

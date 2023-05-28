# Exercise 1-20

> Write a program `detab` that replaces tabs in the input with the proper number of blanks to space to the next tab stop.
> Assume a fixed set of tab stops, say every _n_ columns.
> Should _n_ be a variable or a symbolic parameter.



We choose to make `n` a variable, so that it can be changed by the user of the program (once we’ve learned how to pass arguments to a program).

```c
#include <stdio.h>

#define MAXLEN      10000
#define LENERROR    -1

int tabwidth = 2;

void set_tabwidth(int size);
int replace_tabs(char s[], int max_len);
int getaline(char line[], int lim);

/* Main code */

int main(void)
{
	char line[MAXLEN];

	set_tabwidth(4);

	while (getaline(line, MAXLEN) > 0) {
		replace_tabs(line, MAXLEN);
		printf("%s", line);
	}
	
}

void set_tabwidth(int size)
{
	extern int tabwidth;

	tabwidth = size;
}

int replace_tabs(char s[], int max_len)
{
	int t[max_len];
	int j;
	int spaces;

	j = 0;
	spaces = tabwidth;
	for (int i = 0; i < max_len && s[i] != '\0' && j < max_len; ++i) {
		if (s[i] == '\t') {
			for(; spaces > 0; --spaces) {
				t[j] = ' ';
				++j;
			}
			spaces = tabwidth;
		}
		else {
			t[j] = s[i];
			--spaces;
			if (spaces == 0)
				spaces = tabwidth;
			++j;
		}
	}

	if (j >= max_len) {
		printf("Error: Not enough space to expand with tabwidth %d:\n%s", tabwidth, s);
		return LENERROR;
	}
	t[j] = '\0';

	for (int i = 0; i <= j; ++i) {
		s[i] = t[i];
	}

	return j;
}

int getaline(char s[], int lim)
{
	int c, i;
	
	c = 0;
	for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; ++i)
		s[i] = c;
	if (c == '\n') {
		s[i] = c;
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

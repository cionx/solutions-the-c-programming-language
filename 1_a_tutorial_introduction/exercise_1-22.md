# Exercise 1-22

> Write a program to “fold” long input lines into two or more shorter lines after the last non-blank character that occurs before the _n_-th column of input.
> Make sure your program does something intelligent with very long lines, and if there are no blanks or tabs before the specified column.



### The rules of our program

We will break apart lines, but will not try to combine lines.
We can therefore consider each input line separately.

The basic idea is to go through the input line word for word.
If the word under consideration still fits in the current line, then we put it there.
Otherwise, we print a newline before printing the word.

However, we also need to be concerned with the space between words:
if two subsequent words are supposed to be placed in the same line, then the space between them must also be inserted.
So instead of just considering the next word we also consider the space in front of it, and check if _both of them_ fit into the current row.
If this is the case, then both are added to the current line.
Otherwise, we insert a newline and print the word;
the space that used to be in front of the word will be discarded.

The following is an example of the general behaviour of our program.
Before:
```text
The following is a text block without line breaks:

Lorem ipsum dolor sit amet, consetetur sadipscing elitr, sed diam nonumy eirmod tempor invidunt ut labore et dolore magna aliquyam erat, sed diam voluptua. At vero eos et accusam et justo duo dolores et ea rebum. Stet clita kasd gubergren, no sea takimata sanctus est Lorem ipsum dolor sit amet. Lorem ipsum dolor sit amet, consetetur sadipscing elitr, sed diam nonumy eirmod tempor invidunt ut labore et dolore magna aliquyam erat, sed diam voluptua. At vero eos et accusam et justo duo dolores et ea rebum. Stet clita kasd gubergren, no sea takimata sanctus est Lorem ipsum dolor sit amet. Lorem ipsum dolor sit amet, consetetur sadipscing elitr, sed diam nonumy eirmod tempor invidunt ut labore et dolore magna aliquyam erat, sed diam voluptua. At vero eos et accusam et justo duo dolores et ea rebum. Stet clita kasd gubergren, no sea takimata sanctus est Lorem ipsum dolor sit amet.
```
After:
```text
The following is a text block without line breaks:

Lorem ipsum dolor sit amet, consetetur sadipscing elitr, sed
diam nonumy eirmod tempor invidunt ut labore et dolore magna
aliquyam erat, sed diam voluptua. At vero eos et accusam et
justo duo dolores et ea rebum. Stet clita kasd gubergren, no
sea takimata sanctus est Lorem ipsum dolor sit amet. Lorem
ipsum dolor sit amet, consetetur sadipscing elitr, sed diam
nonumy eirmod tempor invidunt ut labore et dolore magna
aliquyam erat, sed diam voluptua. At vero eos et accusam et
justo duo dolores et ea rebum. Stet clita kasd gubergren, no
sea takimata sanctus est Lorem ipsum dolor sit amet. Lorem
ipsum dolor sit amet, consetetur sadipscing elitr, sed diam
nonumy eirmod tempor invidunt ut labore et dolore magna
aliquyam erat, sed diam voluptua. At vero eos et accusam et
justo duo dolores et ea rebum. Stet clita kasd gubergren, no
sea takimata sanctus est Lorem ipsum dolor sit amet.
```
We also respect pre-existing line breaks.
Before:
```text
Now the same textblock, but with only one sentence per line:

Lorem ipsum dolor sit amet, consetetur sadipscing elitr, sed diam nonumy eirmod tempor invidunt ut labore et dolore magna aliquyam erat, sed diam voluptua.
At vero eos et accusam et justo duo dolores et ea rebum.
Stet clita kasd gubergren, no sea takimata sanctus est Lorem ipsum dolor sit amet.
Lorem ipsum dolor sit amet, consetetur sadipscing elitr, sed diam nonumy eirmod tempor invidunt ut labore et dolore magna aliquyam erat, sed diam voluptua.
At vero eos et accusam et justo duo dolores et ea rebum.
Stet clita kasd gubergren, no sea takimata sanctus est Lorem ipsum dolor sit amet.
Lorem ipsum dolor sit amet, consetetur sadipscing elitr, sed diam nonumy eirmod tempor invidunt ut labore et dolore magna aliquyam erat, sed diam voluptua.
At vero eos et accusam et justo duo dolores et ea rebum.
Stet clita kasd gubergren, no sea takimata sanctus est Lorem ipsum dolor sit amet.
```
After:
```text
Now the same textblock, but with only one sentence per line:

Lorem ipsum dolor sit amet, consetetur sadipscing elitr, sed
diam nonumy eirmod tempor invidunt ut labore et dolore magna
aliquyam erat, sed diam voluptua.
At vero eos et accusam et justo duo dolores et ea rebum.
Stet clita kasd gubergren, no sea takimata sanctus est Lorem
ipsum dolor sit amet.
Lorem ipsum dolor sit amet, consetetur sadipscing elitr, sed
diam nonumy eirmod tempor invidunt ut labore et dolore magna
aliquyam erat, sed diam voluptua.
At vero eos et accusam et justo duo dolores et ea rebum.
Stet clita kasd gubergren, no sea takimata sanctus est Lorem
ipsum dolor sit amet.
Lorem ipsum dolor sit amet, consetetur sadipscing elitr, sed
diam nonumy eirmod tempor invidunt ut labore et dolore magna
aliquyam erat, sed diam voluptua.
At vero eos et accusam et justo duo dolores et ea rebum.
Stet clita kasd gubergren, no sea takimata sanctus est Lorem
ipsum dolor sit amet.
```

If a line begins with whitespace, then this whitespace will be preserved.
(The rationale is that leading whitespace is typically intended by the author, and should therefore not be thown away.)
If a line has leading whitespace and needs to be broken into multiple lines, then the new lines will have no leading whitespace.

Before:
```text
Now the same textblock, but indented by one tab:

  Lorem ipsum dolor sit amet, consetetur sadipscing elitr, sed diam nonumy eirmod tempor invidunt ut labore et dolore magna aliquyam erat, sed diam voluptua.
  At vero eos et accusam et justo duo dolores et ea rebum.
  Stet clita kasd gubergren, no sea takimata sanctus est Lorem ipsum dolor sit amet.
  Lorem ipsum dolor sit amet, consetetur sadipscing elitr, sed diam nonumy eirmod tempor invidunt ut labore et dolore magna aliquyam erat, sed diam voluptua.
  At vero eos et accusam et justo duo dolores et ea rebum.
  Stet clita kasd gubergren, no sea takimata sanctus est Lorem ipsum dolor sit amet.
  Lorem ipsum dolor sit amet, consetetur sadipscing elitr, sed diam nonumy eirmod tempor invidunt ut labore et dolore magna aliquyam erat, sed diam voluptua.
  At vero eos et accusam et justo duo dolores et ea rebum.
  Stet clita kasd gubergren, no sea takimata sanctus est Lorem ipsum dolor sit amet.
```
After:
```text
Now the same textblock, but indented by one tab:

  Lorem ipsum dolor sit amet, consetetur sadipscing elitr,
sed diam nonumy eirmod tempor invidunt ut labore et dolore
magna aliquyam erat, sed diam voluptua.
  At vero eos et accusam et justo duo dolores et ea rebum.
  Stet clita kasd gubergren, no sea takimata sanctus est
Lorem ipsum dolor sit amet.
  Lorem ipsum dolor sit amet, consetetur sadipscing elitr,
sed diam nonumy eirmod tempor invidunt ut labore et dolore
magna aliquyam erat, sed diam voluptua.
  At vero eos et accusam et justo duo dolores et ea rebum.
  Stet clita kasd gubergren, no sea takimata sanctus est
Lorem ipsum dolor sit amet.
  Lorem ipsum dolor sit amet, consetetur sadipscing elitr,
sed diam nonumy eirmod tempor invidunt ut labore et dolore
magna aliquyam erat, sed diam voluptua.
  At vero eos et accusam et justo duo dolores et ea rebum.
  Stet clita kasd gubergren, no sea takimata sanctus est
Lorem ipsum dolor sit amet.
```
If a tab character appears in the text, then its occupied space will be determined relative to a specified `tabsize`.

We have some special cases to consider that arise from long lines.
Let us call a word _overly long_ if it consists of strictly more than _n_ characters, i.e., if it doesn’t fit into a single output line.

- If an entire line consists of a single overly long word (i.e., there are neither other words nor whitespace in the same line), then we do nothing.
  We make no attempts at cutting the word into smaller pieces, and simply let it run over the _n_-th column.

  Before:
  ```text
  Now a very long line with no whitespace in front of it:

  Loremipsumdolorsitamet,consetetursadipscingelitr,seddiamnonumyeirmodtemporinviduntutlaboreetdoloremagnaaliquyamerat,seddiamvoluptua.
  ```
  After:
  ```text
  Now a very long line with no whitespace in front of it:

  Loremipsumdolorsitamet,consetetursadipscingelitr,seddiamnonumyeirmodtemporinviduntutlaboreetdoloremagnaaliquyamerat,seddiamvoluptua.
  ```
  There were no changes.

- If a line begins with whitespace followed by an overly long word, then the word is moved into a new line to make the situation slightly less bad.
  Following our previous rule of not removing leading whitespace, only the whitespace will be left in the original line.
  This is a strange behaviour, but seems to be the one most consistent with the usual rules of our program.

  Before:
  ```text
  Now the same long line, but with some whitespace in front:

                     Loremipsumdolorsitamet,consetetursadipscingelitr,seddiamnonumyeirmodtemporinviduntutlaboreetdoloremagnaaliquyamerat,seddiamvoluptua. 
  ```
  After:
  ```text
  Now the same long line, but with some whitespace in front:

                     
  Loremipsumdolorsitamet,consetetursadipscingelitr,seddiamnonumyeirmodtemporinviduntutlaboreetdoloremagnaaliquyamerat,seddiamvoluptua.
  ```
  Note that the leading whitespace is still there.

- If an overly long word is surrounded by other words, then the overly long word will again be moved into its own line.
  The words before the overly long word and after the overly long word will be processed in the usual way.

  Before:
  ```text
  Now a very long line with whitespace and words in front and words afterwards.

                     Lorem ipsum dolor sit amet, consetetur sadipscing elitr, sed diam nonumy eirmod tempor invidunt ut labore et dolore magna aliquyam erat, sed diam voluptua. Loremipsumdolorsitamet,consetetursadipscingelitr,seddiamnonumyeirmodtemporinviduntutlaboreetdoloremagnaaliquyamerat,seddiamvoluptua. Lorem ipsum dolor sit amet, consetetur sadipscing elitr, sed diam nonumy eirmod tempor invidunt ut labore et dolore magna aliquyam erat, sed diam voluptua.
  ```
  After:
  ```text
  Now a very long line with whitespace and words in front and
  words afterwards.

                     Lorem ipsum dolor sit amet, consetetur
  sadipscing elitr, sed diam nonumy eirmod tempor invidunt ut
  labore et dolore magna aliquyam erat, sed diam voluptua.
  Loremipsumdolorsitamet,consetetursadipscingelitr,seddiamnonumyeirmodtemporinviduntutlaboreetdoloremagnaaliquyamerat,seddiamvoluptua.
  Lorem ipsum dolor sit amet, consetetur sadipscing elitr, sed
  diam nonumy eirmod tempor invidunt ut labore et dolore magna
  aliquyam erat, sed diam voluptua.
  ```



### The piecewise code of our program

We will use `printf` to output the result of our program.
We hence need to include `stdio`.
```c
#include <stdio.h>
```
We will once again work with a fixed maximal line length:
```c
#define MAXLEN 100000
```
Since we haven’t introduced booleans yet, we will fake them:
```c
#define TRUE    1
#define FALSE   0
```
The column size _n_ and tab size will be saved as variables;
this makes it possible for the user to configure these numbers once we’ve learned about passing arguments to functions.
```c
int tabsize;
int columnsize;
```

We will need a variety of functions.
We will use functions to set the tab size and column size.
```c
void set_tabsize(int size);
void set_columnsize(int size);
```
As we go through a line of input, we will need to know if we are currently inside a word or inside a block of whitespace.
For this purpose, we assign each character one of the two roles (apart from `\0`, which is neither).
```c
int inword(char c);
int inws(char c);
```
The output of these functions will be `TRUE` or `FALSE`.
We will use our standard functions to read lines from the input:
```c
int getaline(char line[], int limit);
```
Our two main players are `getword` and `getws`.
These functions give us the word, respectively whitespace at the beginning of the string `line`.
More precisely, they copy the required characters into another string `into`, and then delete the copied characters from the front of `line`.
(We basically treat `line` as a queue that contains words and whitespace in alternating order.)
Both of these functions return the length of the word, respectively whitespace, that they found.
(If `line` begins with whitespace, then `getword` will read off a string of length 0.
Similar for `getws` if the line begins with a non-whitespace character.)
The function `getws` will need to determine how much space the tabs have that it encounters;
for this purpose, we need to tell `getws` at which column of the input line we currently are.
```c
int getword(char line[], char into[]);
int getws(char line[], char into[], int columns);
```
To delete the part of `line` that they have read off, both `getword` and `getws` rely on an auxiliary function `shorten` that removes a specified number of characters from its input string.
```c
void shorten(char s[], int n);
```

The function `getaline` is written as usual:
```c
/* getaline: Reads one line of input with getchar.
 * Returns the length of the line.                  */
int getaline(char line[], int limit)
{
  char c;
  int i;

  c = 0;
  for (i = 0; i < limit - 1 && (c = getchar()) != EOF && c != '\n'; ++i) {
    line[i] = c;
  }
  if (c == '\n') {
    line[i] = '\n';
    ++i;
  }
  line[i] = '\0';
  return i;
}
```

The auxiliary function `shorten` doesn’t do much:
```c
/* shorten: Removes the first n characters from a string s. */
void shorten (char s[], int n)
{
  int i;

  for(i = 0; s[n + i] != '\0'; ++i)
    s[i] = s[n + i];
  s[i] = '\0';
}
```

The function `getword` simply picks up characters until it hits a whitespace character (which includes newline characters):
```c
/* getword: Reads a word from the beginning of a line into
   a provided string. Words are separated by whitespace.
   The found word is then removed from the beginning of the line.
   Returns the length of the found word. */
int getword(char line[], char into[])
{
  int i;

  for(i = 0; inword(line[i]); ++i) {
    into[i] = line[i];
  }
  into[i] = '\0';

  shorten(line, i);

  return i;
}
```

The function `getws` works similarly.
But it also needs to keep track of the current column number, so that the space of tab characters can be correctly calculated.
```c
/* getws: Like getword, but reading off whitespace.
   Returns the length of the found whitespace, which requires
   correctly calculating the space that tabs take. This depends
   on which column of the original input we start off. */
int getws(char line[], char into[], int column)
{
  int i;
  int len;
  extern int tabsize;

  len = 0;
  for(i = 0; inws(line[i]); ++i) {
    into[i] = line[i];
    if (line[i] == ' ') {
      ++len;
    }
    else if (line[i] == '\t') {
      len = len + tabsize - (column % 4);
    }
    /* if line[i] is \n then the length remains unchanged */
  }
  into[i] = '\0';

  shorten(line, i);

  return len;
}
```

The functions `inword` and `inws` are relatively straightforward:
```c
/* inword: checks if we are dealing with non-whitespace */
int inword(char c)
{
  if (c != ' ' && c != '\t' && c != '\n' && c != '\0') {
    return TRUE;
  }
  else {
    return FALSE;
  }
}

/* inws: check if we are dealing with whitespace */
int inws(char c)
{
  if ((c == ' ' || c == '\t' || c == '\n') && c != '\0')
    return TRUE;
  else
    return FALSE;
}
```

The functions `set_columnsize` and `set_tabsize` are also straightforward:
```c
/* set_columnsize: set the value of the variable columnsize */
void set_columnsize(int size)
{
  extern int columnsize;
  columnsize = size;
}

/* set_tabsize: set the value of the variable tabsize */
void set_tabsize(int size)
{
  extern int tabsize;
  tabsize = size;
}
```

#### The `main` function

##### The variables

In our `main` function we need to keep track of various strings and lengths.
We will need space for the current line:
```c
char line[MAXLEN];
```
We will also need space to remember the words and whitespace that we have read off;
thankfully, we only ever need to remember one word and one block of whitespace at a time:
```c
char word[MAXLEN];
char ws[MAXLEN];
```
We will also need the lengths of these strings, as returned by `getword` and `getws`, to know when we have to take a line break:
```c
int wordlen;
int wslen;
```
We need to pass the correct column numbers to `getws`, so we need to keep track off it:
```c
int column;
```
Lastly, some behaviour of our program depends on whether we are at the beginning of a line.
(For example, if we encounter an overly long line, then we need to know if it has to be moved into a new line:
this depends on whether there has already been stuff in the same line or not.)
We hence need to keep track of whether the current output line is still empty:
```c
int emptyline;
```

The rest of our program has the following form
```c
wslen = wordlen = 0;
column = 0;
emptyline = TRUE;

while (getaline(line, MAXLEN) > 0) {
  ⟨process the current line⟩
}

return 0; /* program exits */
```

To process the current line we first reset the column number to `0` and `emptyline` to `TRUE`.
```c
column = 0;
emptyline = TRUE;
```
The tactic for working through a line consists of the following steps (in the specified order):

1.  Read off the leading block of whitespace.

2.  Read off a word.

3.  Check if the combination of whitespace and the word still fit into the current output line.
    If not, then output a new line character.

4.  Print the whitespace and the word if we are still in the same line, otherwise print only the word if we were forced to enter a new line.

We repeat these four steps until the remaining input line is empty.
The resulting loop looks as follows:
```c
while (line[0] != '\0') {
  wslen = getws(line, ws, column);
  wordlen = getword(line, word);
  /* stay in the same line */
  if (columnsize - column >= wslen + wordlen) {
    printf("%s%s", ws, word);
    column = column + wslen + wordlen;
    emptyline = FALSE;
  }
  /* or enter a new line */
  else {
    if (emptyline == TRUE) {
      if (wslen > 0)
        printf("%s\n", ws);
      printf("%s", word);
    }
    else {
      printf("\n%s", word);
    }
    column = wordlen;
    emptyline = FALSE;
  }
}
```

### The complete code

The complete code is as follows:
```c
#include <stdio.h>

#define MAXLEN 100000

#define TRUE    1
#define FALSE   0

int tabsize;
int columnsize;

void set_tabsize(int size);
void set_columnsize(int size);
int inword(char c);
int inws(char c);
int getaline(char line[], int limit);
int getword(char line[], char into[]);
int getws(char line[], char into[], int column);
void shorten(char s[], int n);

int main(void)
{
	extern int columnsize;

	char line[MAXLEN];
	char word[MAXLEN];
	char ws[MAXLEN];
	int wordlen;
	int wslen;

	int column;

	int emptyline;

	set_tabsize(4);
	set_columnsize(60);

	wslen = wordlen = 0;
	column = 0;
	emptyline = TRUE;
	while (getaline(line, MAXLEN) > 0) {
		column = 0;
		emptyline = TRUE;
		while (line[0] != '\0') {
			wslen = getws(line, ws, column);
			wordlen = getword(line, word);
			/* stay in the same line */
			if (columnsize - column >= wslen + wordlen) {
				printf("%s%s", ws, word);
				column = column + wslen + wordlen;
				emptyline = FALSE;
			}
			/* or enter a new line */
			else {
				if (emptyline == TRUE) {
					if (wslen > 0)
						printf("%s\n", ws);
					printf("%s", word);
				}
				else {
					printf("\n%s", word);
				}
				column = wordlen;
				emptyline = FALSE;
			}
		}
	}

	return 0;
}

/* set_columnsize: set the value of the variable columnsize */
void set_columnsize(int size)
{
	extern int columnsize;
	columnsize = size;
}

/* set_tabsize: set the value of the variable tabsize */
void set_tabsize(int size)
{
	extern int tabsize;
	tabsize = size;
}

/* inword: checks if we are dealing with non-whitespace */
int inword(char c)
{
	if (c != ' ' && c != '\t' && c != '\n' && c != '\0') {
		return TRUE;
	}
	else {
		return FALSE;
	}
}

/* inws: check if we are dealing with whitespace */
int inws(char c)
{
	if ((c == ' ' || c == '\t' || c == '\n') && c != '\0')
		return TRUE;
	else
		return FALSE;
}

/* getword: Reads a word from the beginning of a line into
   a provided string. Words are separated by whitespace.
   The found word is then removed from the beginning of the line.
   Returns the length of the found word. */
int getword(char line[], char into[])
{
	int i;

	for(i = 0; inword(line[i]); ++i) {
		into[i] = line[i];
	}
	into[i] = '\0';

	shorten(line, i);

	return i;
}

/* getws: Like getword, but reading off whitespace.
   Returns the length of the found whitespace, which requires
   correctly calculating the space that tabs take. This depends
   on which column of the original input we start off. */
int getws(char line[], char into[], int column)
{
	int i;
	int len;
	extern int tabsize;

	len = 0;
	for(i = 0; inws(line[i]); ++i) {
		into[i] = line[i];
		if (line[i] == ' ') {
			++len;
		}
		else if (line[i] == '\t') {
			len = len + tabsize - (column % 4);
		}
		/* if line[i] is \n then the length remains unchanged */
	}
	into[i] = '\0';

	shorten(line, i);

	return len;
}

/* shorten: Removes the first n characters from a string s. */
void shorten (char s[], int n)
{
	int i;

	for(i = 0; s[n + i] != '\0'; ++i)
		s[i] = s[n + i];
	s[i] = '\0';
}

/* getaline: Reads one line of input with getchar.
 * Returns the length of the line.                  */
int getaline(char line[], int limit)
{
	char c;
	int i;

	c = 0;
	for (i = 0; i < limit - 1 && (c = getchar()) != EOF && c != '\n'; ++i) {
		line[i] = c;
	}
	if (c == '\n') {
		line[i] = '\n';
		++i;
	}
	line[i] = '\0';
	return i;
}
```

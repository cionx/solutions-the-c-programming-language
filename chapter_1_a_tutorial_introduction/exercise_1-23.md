# Exercise 1-23

> Write a program to remove all comments from a C program.
> Don’t forget to handle quoted strings and character constants properly.
> C comments do not nest.



### The general approach

Our program reads through its input one time, line by line, character by character.
While doing so, our program needs to decide if it outputs the current character or not;
the choice depends on whether the character is part of a comment, which in turn depends on previous characters (as well as possible the next character, if the current character is '/').

Our approach is simple:
the program switches through different modes while reading through its input.
The current mode dictates what happens to the characters read while in this mode, and the program has to look out for characters that may change the mode.

More specifically, our program will have five different modes:

0.  **Normal mode**, which covers most of the code.
    It is simply the complement of all following special modes.
    In this mode, every character is simply printed to the output.

1.  **Multiline comment mode**:
    we enter this mode when the character sequence `"/*"` appears in normal mode, and we go back to normal made after the character sequence `"*/"` appears.
    In this mode, no character is printed to the output;
    this includes the character sequences `"/*"` and `"*/"` that start and end this mode respectively.

2.  **Single line comment mode**:[^1]
    we enter this mode when the character sequence `"//"` appears in normal mode, and it holds on until the very end of the line.
    The next line automatically starts back in normal mode.
    In this mode, no character is printed to the output;
    this does not include the newline character at the end of the line, which will be printed.

3.  **String mode**:
    we enter string mode when the character `"` appears in normal mode, and we go back into normal mode after this character reappears and is directly preceded by an even number of backslashes.
    (Note that this entails the case of no backslashes at all.)
    In string mode, every character is printed to the output, including both the opening `"` and closing `"`.

4.  **Character mode** works the same as string mode, but with `'` instead of `"`.

Note that we may go from normal mode to every other mode, depending on the characters that appear in the input, and that afterwords we always go back to normal mode.



### The basic code

We start with an outer loop that goes line-wise through the input.
To read off these lines, we use the usual `getaline` function.
```c
#include <stdio.h>

⋮

#define MAXLEN  100000

⋮

int main(void)
{
	char line[MAXLEN];

	⋮

	while (getaline(line, MAXLEN) > 0) {
		⟨work through the line⟩
	}

	return 0;
}
```

We will use an index to iterate through the current line:
```c
int main(void)
{
	⋮

	int i;

	while (getaline(line, MAXLEN) > 0) {
		i = 0;
    while (line[i] != '\0') {
			⟨consider the character line[i]⟩
		}
	}

	return 0;
}
```

The idea for the innermost code piece is simple:
while in a specific mode, work through as many characters as possible until we either enter a new mode or hit the end of the current line.
The basic layout of the inner part should therefore look as follows:
```c
while (line[i] != '\0') {
	while (in normal mode and line[i] != '\0') {
		⟨process line[i] using the rules of normal mode⟩
		++i;
	}
	while (in multiline comment mode and line[i] != '\0') {
		⟨process line[i] using the rules of multiline comment mode⟩
		++i;
	}
	⋮
	while (in character mode and line[i] != '\0') {
		⟨process line[i] using the rules of character mode⟩
		++i;
	}
}
```
We want to point out some explicit observations regarding our approach:

- We only enter one of the inner loops if we are in the correct mode:
  no character is ever processed in the wrong mode.

- We leave one of the inner loops when we either change the mode during one of its iterations, or have reached the end of the line.

- The outer loop ensures that we repeatedly check all possible modes.
  As our program will always be in one of the five modes, this means that we will always make some progress in one of the inner loop for each iteration of the outer loop.
  This ensures that we will eventually reach the end of the `line`, at which point we leave all depicted loops.

- The inner loops use the index variable `i` to communicate the current position to the other loops:
  if one loop ends by a change of mode, then the next loop will know where to continue reading the `line`.

Before we shift our attention to the inner workings of the inner loops, we still need to make it possible for these inner loops to communicate the current mode:
if the mode of our program changes during the (then final) iteration of one loop, then the other loops need to know which mode is next.
To this end, we introduce an additional mode variable, which exists on the same level as the index variable `i`.
```c
⋮

#define NORMAL          0
#define COMMENT_MULTI   1
#define COMMENT_SINGLE  2
#define STRING          3
#define CHARACTER       4

⋮

int main(void)
{
	⋮

	int mode;

	⋮

	mode = NORMAL;
	while (getaline(line, MAXLEN) > 0) {
		i = 0;
		while (line[state[1]] != '\0') {
			⋮
		}
	}

	return 0;
}
```

Let us now come the workings of the five inner loops that represent the five different modes of our program.
We start with the worst one, the one belonging to the normal mode:
```c
char c;

while (mode == NORMAL && (c = line[i]) != '\0') {
	if (c == '/') {
		if (line[i + 1] == '*') {
			mode = COMMENT_MULTI;
			++i;
		}
		else if (line[i + 1] == '/') {
			mode = COMMENT_SINGLE;
			++i;
		}
		else
			putchar('/');
	}
	else if (c == '\"') {
		putchar('\"');
		mode = STRING;
	}
	else if (c == '\'') {
		putchar('\'');
		mode = CHARACTER;
	}
	else
		putchar(c);
	++i;
}
```
The outermost if-else chain check for characters that could make us enter another mode.
(We don’t use switch statements since the book has yet to introduce this construct.)
We used an auxiliary variable `c` to make the code slightly more readable.

The code for the multiline comment mode is less convoluted:
```c
while (mode == COMMENT_MULTI && line[i] != '\0') {
	if (line[i] == '*' && line[i + 1] == '/') {
		mode = NORMAL;
		++i;
	}
	++i;
}
```
The code for the single line comment mode is similarly simple:
```c
if (mode == COMMENT_SINGLE) {
	while (line[i] != '\0')
		i++;
	putchar('\n');
	mode = NORMAL;
}
```
Note that we have slightly altered the general code from the expected `while (mode == COMMENT_SINGLE && line[i] != '\0')`:
we already know that the single line comment mode will last until the end of the line, so we don’t need to check it for every character in the rest of the line.

The code for the string mode is needs to make sure that we properly recognize if an occurring `"` is escaped or not.
To this end, we need to check if this `"` is preceded by an even number of backslashes (which then means that it is _not_ escaped).
We use the fact that we have access to the entire `line` to go backwards while counting the backslashes we encounter.[^2]
```c
while (mode == STRING && line[i] != '\0') {
	putchar(line[i]);
	if (line[i] == '\"') {
		int backslashes;
		backslashes = 0;
		for (int j = i - 1; j > 0 && line[i] == '\\'; --j)
			++backslashes;
		if (backslashes % 2 == 0)
			mode = NORMAL;
	}
	++i;
}
```
The code for the character mode is the same as for the string mode:
```c
while (mode == CHARACTER && line[i] != '\0') {
	putchar(line[i]);
	if (line[i] == '\'') {
		int backslashes;
		backslashes = 0;
		for (int j = i - 1; j > 0 && line[i] == '\\'; --j)
			++backslashes;
		if (backslashes % 2 == 0)
			mode = NORMAL;
	}
	++i;
}
```



### Some refactoring

Our current code, while functional, isn’t all that pretty to look at:
```c
char c;

⋮

mode = NORMAL;
while (getaline(line, MAXLEN) > 0) {
	i = 0;
	while (line[i] != '\0') {

		while (mode == NORMAL && (c = line[i]) != '\0') {
			if (c == '/') {
				if (line[i + 1] == '*') {
					mode = COMMENT_MULTI;
					++i;
				}
				else if (line[i + 1] == '/') {
					mode = COMMENT_SINGLE;
					++i;
				}
				else
					putchar('/');
			}
			else if (c == '\"') {
				putchar('\"');
				mode = STRING;
			}
			else if (c == '\'') {
				putchar('\'');
				mode = CHARACTER;
			}
			else
				putchar(c);
			++i;
		}

		while (mode == COMMENT_MULTI && line[i] != '\0') {
			if (line[i] == '*' && line[i + 1] == '/') {
				mode = NORMAL;
				++i;
			}
			++i;
		}

		if (mode == COMMENT_SINGLE) {
			while (line[i] != '\0')
				i++;
			putchar('\n');
			mode = NORMAL;
		}

		while (mode == STRING && line[i] != '\0') {
			putchar(line[i]);
			if (line[i] == '\"') {
				int backslashes;
				backslashes = 0;
				for (int j = i - 1; j > 0 && line[i] == '\\'; --j)
					++backslashes;
				if (backslashes % 2 == 0)
					mode = NORMAL;
			}
			++i;
		}

		while (mode == CHARACTER && line[i] != '\0') {
			putchar(line[i]);
			if (line[i] == '\'') {
				int backslashes;
				backslashes = 0;
				for (int j = i - 1; j > 0 && line[i] == '\\'; --j)
					++backslashes;
				if (backslashes % 2 == 0)
					mode = NORMAL;
			}
			++i;
		}
	}
```

To make our code more readable and our program more modular, we will move each of the five loops into their own function.
We call these functions _crawlers_, as they crawl through the text.

However, there is a problem:
the loops use the variables `i` and `mode`, which were defined in the `main` function, to communicate with each other.
If we move the loops into their own respective functions, then this won’t be possible anymore.
The crawlers cannot communicate with one another!

We _could_ fix this problem by making `i` and `mode` into global variables.
But global variables are evil and will burn down my house, so let’s not do that.

We will instead use somewhat of hack:
we will abuse the fact that arrays, when used as a function argument, are not passed by value but by reference.
This then allows the function to update the entries of this array, and the rest of the program to access these update entries.

We will combine the variables `mode` and `i` into a variable `state` of type `int[2]`:
the entry `state[0]` will serve as `mode`, and the entry `state[1]` as `i`.
This variable, together with `line`, will then be passed to the crawlers.
We can convert each of the above code snippets into a crawler by using the following boilerplate code:
```c
void crawler_⟨mode⟩(char line[], int state[])
{
	int mode;
	int i;
	mode = state[0];
	i = state[1];

	⟨previous code of the mode at hand⟩

	state[0] = mode;
	state[1] = i;
}
```

We would also like to make `line` part of `state`, but this doesn’t seem possible for type reasons.



### The final code

Our final code is as follows:
```c
#include <stdio.h>

#define NORMAL          0
#define COMMENT_MULTI   1
#define COMMENT_SINGLE  2
#define STRING          3
#define CHARACTER       4

#define MAXLEN          100000



int getaline(char line[], int limit);
void crawler_normal(char line[], int state_index[]);
void crawler_comment_multiline(char line[], int state_index[]);
void crawler_comment_singleline(char line[], int state_index[]);
void crawler_string(char line[], int state_index[]);
void crawler_character(char line[], int state_index[]);



int main(void)
{
	char line[MAXLEN];
	int state[2]; /* first entry is the current mode,
	                 second entry the current position in the line */

	state[0] = NORMAL;
	while (getaline(line, MAXLEN) > 0) {
		state[1] = 0;
		while (line[state[1]] != '\0') {
			crawler_normal(line, state);
			crawler_comment_multiline(line, state);
			crawler_comment_singleline(line, state);
			crawler_string(line, state);
			crawler_character(line, state);
		}
	}

	return 0;
}



void crawler_normal(char line[], int state[])
{
	char c;
	int mode;
	int i;
	mode = state[0];
	i = state[1];

	while (mode == NORMAL && (c = line[i]) != '\0') {
		if (c == '/') {
			if (line[i + 1] == '*') {
				mode = COMMENT_MULTI;
				++i;
			}
			else if (line[i + 1] == '/') {
				mode = COMMENT_SINGLE;
				++i;
			}
			else
				putchar('/');
		}
		else if (c == '\"') {
			putchar('\"');
			mode = STRING;
		}
		else if (c == '\'') {
			putchar('\'');
			mode = CHARACTER;
		}
		else
			putchar(c);
		++i;
	}

	state[0] = mode;
	state[1] = i;
}



void crawler_comment_multiline(char line[], int state[])
{
	int mode;
	int i;
	mode = state[0];
	i = state[1];

	while (mode == COMMENT_MULTI && line[i] != '\0') {
		if (line[i] == '*' && line[i + 1] == '/') {
			mode = NORMAL;
			++i;
		}
		++i;
	}

	state[0] = mode;
	state[1] = i;
}



void crawler_comment_singleline(char line[], int state[])
{
	int mode;
	int i;
	mode = state[0];
	i = state[1];

	if (mode == COMMENT_SINGLE) {
		while (line[i] != '\0')
			++i;
		putchar('\n');
		mode = NORMAL;
	}

	state[0] = mode;
	state[1] = i;
}



void crawler_string(char line[], int state[])
{
	int mode;
	int i;
	mode = state[0];
	i = state[1];

	while (mode == STRING && line[i] != '\0') {
		putchar(line[i]);
		if (line[i] == '\"') {
			int backslashes;
			backslashes = 0;
			for (int j = i - 1; j > 0 && line[i] == '\\'; --j)
				++backslashes;
			if (backslashes % 2 == 0)
				mode = NORMAL;
		}
		++i;
	}

	state[0] = mode;
	state[1] = i;
}



void crawler_character(char line[], int state[])
{
	int mode;
	int i;
	mode = state[0];
	i = state[1];

	while (mode == CHARACTER && line[i] != '\0') {
		putchar(line[i]);
		if (line[i] == '\'') {
			int backslashes;
			backslashes = 0;
			for (int j = i - 1; j > 0 && line[i] == '\\'; --j)
				++backslashes;
			if (backslashes % 2 == 0)
				mode = NORMAL;
		}
		++i;
	}

	state[0] = mode;
	state[1] = i;
}



/* getaline: Reads one line of input with getchar.
   Returns the length of the line. */
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



[^1]: These kinds of comments don’t appear in the book.
      We nevertheless decided to support them.
[^2]: If we didn’t have access to the already read parts of the line, then we would need to count the backslashes as we go through the line, and reset this counter to 0 whenever we encounter a non-backslash character.

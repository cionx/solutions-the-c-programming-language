# Exercise 4-6

> Add commands for handling variables.
> (It’s easy to provide twenty-six variables with single-letter names.)
> Add a variable for the most recently printed value.

---



### Last printed value

We use the symbol `_` for the last printed value.
We add a signal for this input:
```c
#define LAST     '_' /* signal for the last printed value */
```
We remember the last printed value, and push it into the stack if an input of type `LAST` appears:
```c
int main(void)
{
	⋮
	double last_printed;

	while ((type = getop(s)) != EOF) {
		switch (type) {
			⋮
			case LAST:
				push(last_printed);
				break;
			case '\n':
				printf("\t%.8g\n", last_printed = pop());
				break;
			⋮
		}
	}

	return 0;
}
```
We can now use `_` to refer to the last printed value:
```text
1 2 +
	3
_ 4 +
	7
_ 5 -
	2
_ _ *
	4
```



### Variables

We use the syntax
```text
#⟨variable name⟩
```
to save the top of the stack into a single-character variable.
For example,
```text
3 2 + #a
```
will save the value `5` into `a`.
To retrieve the value of a variable, simply use that variable name as a placeholder.
For example,
```text
3 2 + #a a a +
```
will result in `10` being the top of the stack.

To implement saving and loading of variables we introduce two new signals:
```c
#define SAVE   '#'  /* signal for saving a variable */
#define LOAD   'a'  /* signal for reading a variable */
```
We also add a function to read off the top of the stack without poping it.
```c
double top(void)
{
	double value = pop();
	push(value);
	return value;
}
```
We extend `getop` with the following two cases:
```c
	if (c == '#') {
		c = getch();
		if ('a' <= c && c <= 'z') {
			s[0] = c;
			return SAVE;
		}
		else {
			printf("error: missing variable name after #\n");
			ungetch(c);
		}
	}

	if ('a' <= c && c <= 'z')
		return LOAD;
```
We also extend `main` with the following two cases:
```c
	⋮
	int var_name;
	double vars[26];
	for (int i = 0; i < 26; ++i)
		vars[i] = 0.0;
	⋮
		⋱
			⋮
			case SAVE:
				var_name = s[0];
				vars[var_name - 'a'] = top();
				break;
			case LOAD:
				var_name = s[0];
				push(vars[var_name - 'a']);
				break;
			⋮
```
We can now use variables, and also use the syntax `_ #⟨variable name⟩` to save the last printed value in a variable.
```text
3 2 + #a
	5
2 a *
	10
_ #b
	10
a b *
	50
```
We can always read off the current value of a variable by simply typing its name:
```text
a
	5
b
	10
```

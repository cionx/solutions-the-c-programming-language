# Exercise 5-1

> As written, `getint` treats a `+` or `-` not followed by a digit as a valid representation of zero.
> Fix it to push such a character back on the input.

---

We use the following `main` function for testing:
```c
int main(void)
{
	int n = 0;
	while (getint(&n) != EOF)
		printf("Read %d\n", n);
	return 0;
}
```
As an example:
```text
123 456 789 ⟨Enter⟩
Read 123
Read 456
Read 789
```
The current program doesn’t deal well with non-integer inputs.
For example, `123a` leads to a loop that endlessly prints `Read 123`.
It is not clear what the correct behaviour should be for a sign that is not followed by a digit.

The described code change can be implemented as follows:
```c
	⋮
	if (c == '-' || c == '+') {
		c = getch();
		if (!isdigit(c)) {
			ungetch(c);
			ungetch((sign == -1) ? '-' : '+');
			return 0;
		}
	}
	⋮
```
A sign followed by a non-digit now also leads to an endless loop.

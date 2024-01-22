# Exercise 4-3

> Given the basic framework, it’s straightforward to extend the calculator.
> Add the modulus (`%`) operator and provisions for negative numbers. □

---

### Modulus

We use the function `fmod` from `math.h` to implement the modulus operation for two doubles.
We add the following case to the `switch` in `main`:
```c
			case '%':
				op2 = pop();
				if (op2 != 0.0)
					push(fmod(pop(), op2));
				else
					printf("error: zero modulus\n");
				break;
```
A word of warning:
to properly compile (and link) the source file we now need to add the option `-lm` to the compiler. See https://stackoverflow.com/questions/5248919/undefined-reference-to-sqrt-or-other-mathematical-functions for more details.



### Negative numbers

We add support for signed numbers with the following code addition/modification:
```c
	⋮
	if (!isdigit(c) && c != '.' && c != '-' && c != '+')
		return c;                            /* not a number */

	i = 0;
	if (c == '-' || c == '+') {              /* handle the sign */
		int next = getch();
		if (!isdigit(next) && next != '.') { /* not a number */
			ungetch(next);
			return c;
		}
		s[++i] = c = next;
	}
	if (isdigit(c)) /* collect integer part */
	⋮
```

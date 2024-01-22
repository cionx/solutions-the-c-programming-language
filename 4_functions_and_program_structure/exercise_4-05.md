# Exercise 4-5

> Add access to library functions like `sin`, `exp`, and `pow`.
> See `<math.h>` in Appendix B, Section 4.

---

We add support for sine, cosine, tangent, the exponential function, and powers via single-character commands.
```c
#include <math.h>
⋮
			case 's':
				push(sin(pop()));
				break;
			case 'c':
				push(cos(pop()));
				break;
			case 't':
				push(tan(pop()));
				break;
			case 'e':
				push(exp(pop()));
				break;
			case 'p':
				op2 = pop();
				push(pow(pop(), op2));
				break;
				⋮
```

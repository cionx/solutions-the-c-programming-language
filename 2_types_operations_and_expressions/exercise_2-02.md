# Exercise 2-2

> Write a loop equivalent to the `for` loop above without using `&&` or `||`.

---

We can always express a loop of the form
```c
for(⟨init code⟩; bool11 && … && bool1n && !bool21 && … && !bool2m; ⟨increase code⟩) {
  ⟨inner code⟩
}
```
with help of an auxiliary boolean variable `cont` (for “continue”) and `if`-`else`-control flows:
```c
for (⟨init code⟩; cont; ⟨increase code⟩) {
	if (bool11) {
		if (bool12) {
			⋱
				if(bool1n) {
					if (bool21)
						cont = false;
					else if (bool21)
						cont = false;
					⋮
					else if (bool2m)
						cont = false;
					else {
						⟨inner code⟩
					}
				}
				else cont = false;
			⋰
		}
		else cont = false;
	}
	else cont = false
}
```

For the given loop, we get the following code:
```c
bool cont = true;
for (i = 0; cont; ++i) {
	if (i < lim - 1) {
		c = getchar();
		if (c == '\n')
			cont = false;
		else if (c == EOF)
			cont = false;
		else
			s[i] = c;
	}
	else
		cont = false;
}
```

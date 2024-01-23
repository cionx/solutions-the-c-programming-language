# Exercise 4-9

> Our `getch` and `ungetch` do not handle a pushed-back `EOF` correctly.
> Decide what their properties ought to be if an `EOF` is pushed back, then implement your design.

---

One problem (maybe the only one?) is that `char` may be unsigned but `EOF` may be negative.
This may lead to conflicts when we try to save `EOF` in `char buf[BUFSIZE]`.
We therefore change the type of `buf` from `char[]` to `int[]`.

# Exercise 1-11

> How would you test the word count program?
> What kinds of input are must likely to uncover bugs if there are any?



To test the program, I can pipe in input file into the compiled `a.out` via `cat ⟨file⟩ | ./a.out`, and then compare the result with `wc ⟨file⟩`:
```text
$ cat hello_world.c | ./a.out
6 8 60

$ wc hello_world.c
 6  8 60 hello_world.c
```

I’m not sure what kinds of input may help to uncover bugs.

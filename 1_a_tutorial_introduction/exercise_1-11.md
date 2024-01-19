# Exercise 1-11

> How would you test the word count program?
> What kinds of input are must likely to uncover bugs if there are any?

---

To test the program, we can pipe an input file into the compiled `a.out` via `cat ⟨file⟩ | ./a.out`, and then compare the result with `wc ⟨file⟩`:
```text
$ cat hello_world.c | ./a.out
6 8 60

$ wc hello_world.c
 6  8 60 hello_world.c
```

The program should be tested against
- an empty file,
- files consisting entirely of one very long line,
- files with (multiple) empty lines,
- very long files,
- UTF-8 files.

# Exercise 1-9

> Write a program to copy its input to its output, replacing each string of one or more blanks by a single blank.

---

We start with the program from subsection 1.5.1 that simply copies its input to its output.
But whenever we encounter a blank, we gobble up all following blanks.
We only stop once we have arrived at a non-blank character.
Before returning to the main loop we have to output this non-blank character, because otherwise it would get overwritten by the next call to `getchar` before it had the chance of getting to the output.
```c
#include <stdio.h>

int main(void)
{
	int c;

	c = 0; /* Dummy initial value. */
	while ((c = getchar()) != EOF) {
		putchar(c);
		if (c == ' ') {
			while ((c = getchar()) == ' ')
				;
			putchar(c);
		}
	}
}
```

We test our program with the following text:
```text
a b  c   d    e     f      g
a      b     c    d   e  f g


a b c d e f g
a  b  c  d  e  f  g
a   b   c   d   e   f   g
a    b    c    d    e    f    g
a     b     c     d     e     f     g


Lorem ipsum dolor   sit       amet,        consetetur   sadipscing    elitr,    sed       diam     nonumy     eirmod  tempor       invidunt   ut          labore et   dolore    magna      aliquyam   erat,   sed    diam        voluptua.       At    vero     eos     et  accusam  et          justo  duo     dolores        et          ea         rebum. Stet    clita kasd    gubergren, no          sea        takimata        sanctus         est Lorem       ipsum         dolor      sit         amet.  Lorem       ipsum  dolor      sit  amet,     consetetur   sadipscing elitr,          sed   diam nonumy      eirmod    tempor invidunt       ut   labore    et         dolore         magna    aliquyam      erat,    sed         diam         voluptua.   At   vero  eos   et        accusam          et       justo       duo          dolores      et   ea   rebum.      Stet  clita     kasd   gubergren,        no         sea        takimata         sanctus est        Lorem   ipsum dolor     sit amet.    Lorem ipsum      dolor        sit   amet,        consetetur        sadipscing   elitr,  sed         diam    nonumy      eirmod         tempor   invidunt  ut labore     et        dolore    magna          aliquyam         erat,     sed      diam         voluptua.       At        vero          eos       et   accusam          et   justo      duo        dolores  et          ea         rebum.          Stet  clita      kasd  gubergren,    no     sea      takimata     sanctus     est   Lorem    ipsum   dolor    sit      amet.
```

The output is as it should be:
```text
a b c d e f g
a b c d e f g


a b c d e f g
a b c d e f g
a b c d e f g
a b c d e f g
a b c d e f g


Lorem ipsum dolor sit amet, consetetur sadipscing elitr, sed diam nonumy eirmod tempor invidunt ut labore et dolore magna aliquyam erat, sed diam voluptua. At vero eos et accusam et justo duo dolores et ea rebum. Stet clita kasd gubergren, no sea takimata sanctus est Lorem ipsum dolor sit amet. Lorem ipsum dolor sit amet, consetetur sadipscing elitr, sed diam nonumy eirmod tempor invidunt ut labore et dolore magna aliquyam erat, sed diam voluptua. At vero eos et accusam et justo duo dolores et ea rebum. Stet clita kasd gubergren, no sea takimata sanctus est Lorem ipsum dolor sit amet. Lorem ipsum dolor sit amet, consetetur sadipscing elitr, sed diam nonumy eirmod tempor invidunt ut labore et dolore magna aliquyam erat, sed diam voluptua. At vero eos et accusam et justo duo dolores et ea rebum. Stet clita kasd gubergren, no sea takimata sanctus est Lorem ipsum dolor sit amet.
```

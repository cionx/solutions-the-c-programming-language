# Exercise 1-19

> Write a function `reverse(s)` that reverses the character string `s`.
> Use it to write a program that reverses its input a line at a time.

---

The function `reverse` first determined the length of its input.
It then swaps the first character with the last one, then the second one with the second-to-last one, and so on.
```c
void reverse(char s[])
{
	int last_index;

	last_index = 0;
	while (s[last_index] != '\0')
		++last_index;
	--last_index;

	for (int i = 0; i < last_index - i; ++i) {
		char tmp;
		tmp = s[i];
		s[i] = s[last_index - i];
		s[last_index - i] = tmp;
		
	}
}
```
The reverse lines, we use an auxiliary procedure `reverse_line` that takes care of the line break at the end of a line.
```c
void reverse_line(char line[], int length)
{
	if (line[length - 1] == '\n') {
		line[length - 1] = '\0';
		reverse(line);
		line[length - 1] = '\n';
	}
	else
		reverse(line);
}
```
Finally, the main function:
```c
int main(void)
{
	int len;
	char line[MAXLINE];

	while ((len = getaline(line, MAXLINE)) > 0) {
		reverse_line(line, len);
		printf("%s", line);
	}

  return 0;
}
```

Altogether, we get the following code:
```c
#include <stdio.h>

#define MAXLINE 100000

void reverse(char s[]);
void reverse_line(char line[], int length);
int getaline(char s[], int lim);

int main(void)
{
	int len;
	char line[MAXLINE];

	while ((len = getaline(line, MAXLINE)) > 0) {
		reverse_line(line, len);
		printf("%s", line);
	}

	return 0;
}

void reverse_line(char line[], int length)
{
	if (line[length - 1] == '\n') {
		line[length - 1] = '\0';
		reverse(line);
		line[length - 1] = '\n';
	}
	else
		reverse(line);
}

void reverse(char s[])
{
	int last_index;

	last_index = 0;
	while (s[last_index] != '\0')
		++last_index;
	--last_index;

	for (int i = 0; i < last_index - i; ++i) {
		char tmp;
		tmp = s[i];
		s[i] = s[last_index - i];
		s[last_index - i] = tmp;
	}
}

int getaline(char s[], int lim)
{
	int c, i;

	c = 0;
	for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; ++i)
		s[i] = (char) c;
	if (c == '\n') {
		s[i] = (char) c;
		++i;
	}
	s[i] = '\0';
	return i;
}
```

We can test this program with its own source code:
```text
>h.oidts< edulcni#

000001 ENILXAM enifed#

;)][s rahc(esrever diov
;)htgnel tni ,][enil rahc(enil_esrever diov
;)mil tni ,][s rahc(enilateg tni

)diov(niam tni
{
;nel tni	
;]ENILXAM[enil rahc	

{ )0 > ))ENILXAM ,enil(enilateg = nel(( elihw	
;)nel ,enil(enil_esrever		
;)enil ,"s%"(ftnirp		
}	

;0 nruter	
}

)htgnel tni ,][enil rahc(enil_esrever diov
{
{ )'n\' == ]1 - htgnel[enil( fi	
;'0\' = ]1 - htgnel[enil		
;)enil(esrever		
;'n\' = ]1 - htgnel[enil		
}	
esle	
;)enil(esrever		
}

)][s rahc(esrever diov
{
;xedni_tsal tni	

;0 = xedni_tsal	
)'0\' =! ]xedni_tsal[s( elihw	
;xedni_tsal++		
;xedni_tsal--	

{ )i++ ;i - xedni_tsal < i ;0 = i tni( rof	
;pmt rahc		
;]i[s = pmt		
;]i - xedni_tsal[s = ]i[s		
;pmt = ]i - xedni_tsal[s		
}	
}

)mil tni ,][s rahc(enilateg tni
{
;i ,c tni	

;0 = c	
)i++ ;'n\' =! c && FOE =! ))(rahcteg = c( && 1 - mil < i ;0 = i( rof	
;c )rahc( = ]i[s		
{ )'n\' == c( fi	
;c )rahc( = ]i[s		
;i++		
}	
;'0\' = ]i[s	
;i nruter	
}
```
(This output has tabs at the _end_ of lines – truly awful.)

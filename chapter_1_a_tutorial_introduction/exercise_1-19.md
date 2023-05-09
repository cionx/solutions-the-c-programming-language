# Exercise 1-19

> Write a function `reverse(s)` that reverses the character string `s`.
> Use it to write a program that reverses its input a line at a time.



The function `reverse` first determined the length of its input.
It then swaps the first entry with the last one, then the second one with the second-to-last one, and so on.
```c
void reverse(char s[])
{
	int length;

	length = 0;
	while (s[length] != '\0')
		++length;

	for (int i = 0; i < length - 1 - i; ++i) {
		char c;
		c = s[i];
		s[i] = s[length - 1 - i];
		s[length - 1 - i] = c;
	}
}
```
The reverse lines, we use an auxiliary procedure `reverse_line` that takes care of the linebreak at the end of a line.
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
Finally, a the main function:
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

#define MAXLINE 1000

void reverse(char s[]);
void reverse_line(char line[], int length);
int getaline (char s[], int lim);

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
	int length;

	length = 0;
	while (s[length] != '\0')
		++length;

	for (int i = 0; i < length - 1 - i; ++i) {
		char c;
		c = s[i];
		s[i] = s[length - 1 - i];
		s[length - 1 - i] = c;
	}
}

int getaline(char s[], int lim)
{
	int c, i;
	
	c = 0;
	for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; ++i)
		s[i] = c;
	if (c == '\n') {
		s[i] = c;
		++i;
	}
	s[i] = '\0';
	return i;
}
```

We can test this program with its own source code:
```text
$ cat exercise_1-19.c | ./a.out
>h.oidts< edulcni#

0001 ENILXAM enifed#

;)][s rahc(esrever diov
;)htgnel tni ,][enil rahc(enil_esrever diov
;)mil tni ,][s rahc( enilateg tni

)diov(niam tni
{
;nel tni	
;]ENILXAM[enil rahc	

{ )0 > ))ENILXAM ,enil(enilateg = nel(( elihw	
;)nel ,enil(enil_esrever		
;)enil ,"s%"(ftnirp		
}	
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
;htgnel tni	

;0 = htgnel	
)'0\' =! ]htgnel[s( elihw	
;htgnel++		

{ )i++ ;i - 1 - htgnel < i ;0 = i tni( rof	
;c rahc		
;]i[s = c		
;]i - 1 - htgnel[s = ]i[s		
;c = ]i - 1 - htgnel[s		
}	
}

)mil tni ,][s rahc(enilateg tni
{
;i ,c tni	
	
;0 = c	
)i++ ;'n\' =! c && FOE =! ))(rahcteg = c( && 1 - mil < i ;0 = i( rof	
;c = ]i[s		
{ )'n\' == c( fi	
;c = ]i[s		
;i++		
}	
;'0\' = ]i[s	
;i nruter	
}
```
(This output has tabs at the _end_ of lines – truly aweful.)

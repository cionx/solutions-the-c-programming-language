#include <stdio.h>

void reverse(char *s);

/* reverse(s): reverse string s in place; pointer version */
void reverse(char *s)
{
	/* Handle the empty string by hand */
	if (*s == '\0')
		return;

	char *t = s;
	while (*t != '\0')        /* We have at least one iteration... */
		++t;
	--t;                      /* ... so that s <= t... */
	for (; s < t; ++s, --t) { /* ... allowing for pointer comparion. */
		char tmp;
		tmp = *s;
		*s = *t;
		*t = tmp;
	}
}

int main(void)
{
	char strings[][8] = {"",     "a",     "ab",     "abc",
	                     "abcd", "abcde", "abcdef", "abcdefg"};
	for (int i = 0; i < 8; ++i) {
		printf("\"%s\" becomes ", strings[i]);
		reverse(strings[i]);
		printf("\"%s\"\n", strings[i]);
	}

	return 0;
}

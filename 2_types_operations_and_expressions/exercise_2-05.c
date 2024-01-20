#include <stdbool.h>
#include <stdio.h>

int any(const char str1[], const char str2[]);
bool instring(char c, const char str[]);

int any(const char str1[], const char str2[])
{
	for (int i = 0; str1[i] != '\0'; ++i)
		if (instring(str1[i], str2))
			return i;

	return -1;
}

bool instring(char c, const char str[])
{
	for (int i = 0; str[i] != '\0'; ++i) {
		if (c == str[i])
			return true;
	}
	return false;
}

int main(void)
{
	char s[] = "anywhere";
	char vowels[] = "xyz";
	printf("\"%s\" contains a character from \"%s\" at position %d.\n", s,
	       vowels, any(s, vowels));

	return 0;
}

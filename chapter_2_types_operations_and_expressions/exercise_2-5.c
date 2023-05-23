#include <stdbool.h>
#include <stdio.h>

int any(char str1[], char str2[]);
bool in_string(char c, char str[]);

int any(char str1[], char str2[])
{
	for (int i = 0; str1[i] != '\0'; ++i)
		if (in_string(str1[i], str2))
			return i;

	return -1;
}

bool in_string(char c, char str[])
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

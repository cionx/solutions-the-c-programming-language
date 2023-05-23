#include <stdbool.h>
#include <stdio.h>

void squeeze(char str1[], char str2[]);
bool in_string(char c, char str[]);

void squeeze(char str1[], char str2[])
{
	int i, j;
	for (i = j = 0; str1[i] != '\0'; ++i)
		if (!in_string(str1[i], str2))
			str1[j++] = str1[i];
	str1[j] = '\0';
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
	char s[] = "Lorem ipsum dolor";
	char vowels[] = "aeiou";
	printf("\"%s\" without \"%s\" is ", s, vowels);
	squeeze(s, vowels);
	printf("\"%s\"\n", s);

	return 0;
}

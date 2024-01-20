#include <stdbool.h>
#include <stdio.h>

void squeeze(char str1[], const char str2[]);
bool instring(char c, const char str[]);

void squeeze(char str1[], const char str2[])
{
	int from, to;
	for (from = to = 0; str1[from] != '\0'; ++from)
		if (!instring(str1[from], str2))
			str1[to++] = str1[from];
	str1[to] = '\0';
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
	char s[] = "Lorem ipsum dolor";
	char vowels[] = "aeiou";
	printf("\"%s\" without \"%s\" is ", s, vowels);
	squeeze(s, vowels);
	printf("\"%s\"\n", s);

	return 0;
}

#include <stdbool.h>

int strindex(char const *s, char const *t);
bool startswith(char const *s, char const *t);

/* strindex(s, t): index of first occurrence of t in s */
int strindex(char const *s, char const *const t)
{
	char const *const start = s;
	for (; *s != '\0'; ++s)
		if (startswith(s, t))
			return (int) (s - start);
	if (*t == '\0')
		return 0;
	else
		return -1;
}

/* startswith(s, t): checks if s starts with t */
bool startswith(char const s[], char const t[])
{
	/* We go through s until we either found a difference or have gone through
	 * all of t. */
	while (*s == *t && *t != '\0')
		++s, ++t;
	return *t == '\0';
}

/* TESTING */

#include <stdio.h>

int main(void)
{
	char const *const strings[][2] = {
		{"", ""},      {"", "a"},      {"a", ""},    {"a", "a"},
		{"abc", "a"},  {"abc", "b"},   {"abc", "c"}, {"abc", "ab"},
		{"abc", "bc"}, {"abc", "abc"}, {"abc", "d"}, {"abc", "ad"}};

	for (int i = 0; i < 12; ++i) {
		char const *const s = strings[i][0];
		char const *const t = strings[i][1];
		printf("\"%s\" in \"%s\": %d\n", t, s, strindex(s, t));
	}
}

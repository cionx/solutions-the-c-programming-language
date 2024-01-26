/* STRNCPY */

char *my_strncpy(char *to, char const *from, int n);
char *my_strncat(char *to, char const *from, int n);
int my_strncmp(char const *s, char const *t, int n);

char *my_strncpy(char *to, const char *from, int n)
{
	char *const start = to;

	while (n-- > 0 && (*to++ = *from++) != '\0')
		;
	while (n-- > 0)
		*to++ = '\0';

	return start;
}

char *my_strncat(char *to, char const *from, int n)
{
	char *const start = to;

	while (*to != '\0') /* get the end of `to` */
		++to;
	while (n-- > 0 && (*to = *from) != '\0')
		to++, from++;
	*to = '\0';

	return start;
}

int my_strncmp(char const *s, char const *t, int n)
{
	for (; n > 0 && *s == *t; --n, ++s, ++t)
		if (*s == '\0')
			/* we reached the end of s and t without finding a difference */
			return 0;
	if (n <= 0)
		return 0;
	else
		return *s - *t;
}

/* TESTING */

#include <stdio.h>

void printArray(char arr[], int size);

void printArray(char arr[], int size)
{
	printf("[");
	for (int i = 0; i < size; ++i)
		printf("%d ", arr[i]);
	printf("]\n");
}

int main(void)
{
	printf("STRNCPY\n");
	char s1[] = "aaaaaaaaaa"; /* 10 a’s */
	char t1[] = "bcd";
	printf("target:\t");
	printArray(s1, 11);
	printf("source:\t");
	printArray(t1, 4);
	for (int n = 0; n <= 11; ++n) {
		char s1[] = "aaaaaaaaaa";
		printf("n = %d:\t", n);
		my_strncpy(s1, t1, n);
		printArray(s1, 11);
	}

	printf("\n\n");
	printf("STRNCAT\n");
	char s2[] = {'a', 'b', 'c', '\0', '\0', '\0', 'g', 'h', 'i', 'j', 'k'};
	char t2[] = "def";
	printf("target:\t");
	printArray(s2, 11);
	printf("source:\t");
	printArray(t2, 4);
	for (int n = 0; n <= 6; ++n) {
		char s2[] = {'a', 'b', 'c', '\0', '\0', '\0', 'g', 'h', 'i', 'j', 'k'};
		printf("n = %d:\t", n);
		my_strncat(s2, t2, n);
		printArray(s2, 11);
	}

	printf("\n\n");
	printf("STRNCMP\n");
	char *s = "abc";
	char *t = "abcdef";
	char *u = "abcddd";
	printf("s:\t\"%s\"\n", s);
	printf("t:\t\"%s\"\n", t);
	printf("u:\t\"%s\"\n", u);

	printf("\n");
	for (int n = 0; n < 4; ++n)
		printf("s, s, n = %d\t%d\n", n, my_strncmp(s, s, n));
	printf("\n");
	for (int n = 0; n < 7; ++n)
		printf("s, t, n = %d\t%d\n", n, my_strncmp(s, t, n));
	printf("\n");
	for (int n = 0; n < 7; ++n)
		printf("t, u, n = %d\t%d\n", n, my_strncmp(t, u, n));

	return 0;
}

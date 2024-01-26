#include <stdbool.h>
#include <stdio.h>

void itoa(int n, char *s);
void reverse(char *s);

void itoa(int n, char *s)
{
	char *const start = s;
	bool negative = (n < 0);

	if (n > 0)
		n = -n;
	do {
		*s++ = -(n % 10) + '0';
		n /= 10;
	} while (n != 0);
	if (negative)
		*s++ = '-';
	*s = '\0';
	reverse(start);
}

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

/* TESTING */

#include <limits.h>

int main(void)
{
	int nums[] = {123, -123, 0, INT_MAX, INT_MIN};
	char s[10];
	for (int i = 0; i < 5; ++i) {
		itoa(nums[i], s);
		printf("%d becomes \"%s\"\n", nums[i], s);
	}
}

#include <ctype.h>
#include <stdio.h>

void expand(char source[], char target[]);

void expand(char source[], char target[])
{
	if ((target[0] = source[0]) == '\0')
		return;

	int to = 1;
	for (int from = 1; source[from] != '\0'; ++from) {
		if (source[from] != '-')
			target[to++] = source[from];
		else {
			char before = source[from - 1]; /* Okay because from starts as 1. */
			char after = source[from + 1];
			if ((isdigit(before) && isdigit(after)) ||
			    (islower(before) && islower(after)) ||
			    (isupper(before) && isupper(after))) {
				char direction = (before <= after) ? 1 : -1;
				for (char c = before + direction; c != after; c += direction)
					target[to++] = c;
			}
			else
				target[to++] = '-';
		}
		target[to] = '\0';
	}
}

int main(void)
{
	char output[1000];
	char *input[] = {"a-z",  "A-Z",   "0-9", "a-b-c", "a-z0-9", "-a-z",
	                 "a-z-", "-a-z-", "a-Z", "0-a",   "a-0",    "a-z-a-z"};
	int inputlen = 12;

	for (int i = 0; i < inputlen; ++i) {
		expand(input[i], output);
		printf("\"%s\" becomes \"%s\"\n", input[i], output);
	}

	return 0;
}

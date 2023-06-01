#include <ctype.h>
#include <stdio.h>

void expand(char s1[], char s2[]);

void expand(char s1[], char s2[])
{
	if ((s2[0] = s1[0]) == '\0')
		return;

	int j = 1;
	for (int i = 1; s1[i] != '\0'; ++i) {
		if (s1[i] != '-')
			s2[j++] = s1[i];
		else {
			char c1 = s1[i - 1]; /* Okay because i starts as 1. */
			char c2 = s1[i + 1];
			if ((isdigit(c1) && isdigit(c2)) || (islower(c1) && islower(c2)) ||
			    (isupper(c1) && isupper(c2))) {
				char direction = (c1 <= c2) ? 1 : -1;
				for (char c = c1 + direction; c != c2; c += direction)
					s2[j++] = c;
			}
			else
				s2[j++] = s1[i];
		}
		s2[j] = '\0';
	}
}

int main(void)
{
	char output[1000];
	char *input[] = {"a-z",  "A-Z", "0-9", "a-b-c", "a-z0-9",
	                 "-a-z", "a-Z", "0-a", "a-0",   "a-z-a-z"};
	int inputlen = 10;

	for (int i = 0; i < inputlen; ++i) {
		expand(input[i], output);
		printf("\"%s\" becomes \"%s\"\n", input[i], output);
	}

	return 0;
}

#include <stdio.h>

void reverse(char s[]);
int helper(char s[], int from, int to);

void reverse(char s[])
{
	helper(s, 0, 0);
}

/* helper(s, from, to): reverses the substring starting at position `from` and
 * insert the result starting with position `to`. Returns the position of the
 * last character of the reversed substring.
 * Example:
 *         ____
 *  s = abcdefg   from = 3  to = 1
 *
 *  becomes
 *       ____
 *      agfedfg
 */

int helper(char s[], int from, int to)
{
	char c = s[from];

	if (c == '\0')
		return to - 1;

	int pos = helper(s, from + 1, to) + 1;
	s[pos] = c;
	return pos;
}

int main(void)
{
	char s[] = "abcdefg";
	printf("\"%s\" becomes ", s);
	reverse(s);
	printf("\"%s\"\n", s);
	return 0;
}

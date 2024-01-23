# Exercise 4-13

- Write a recursive version of the function `reverse(s),` which reverses the string `s` in place.

---

We use the following code:
```c
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
```

We test our code with the string `"abcdefg"`:
```c
int main(void)
{
	char s[] = "abcdefg";
	printf("\"%s\" becomes ", s);
	reverse(s);
	printf("\"%s\"\n", s);
	return 0;
}
```
The output is as desired:
```text
"abcdefg" becomes "gfedcba"
```

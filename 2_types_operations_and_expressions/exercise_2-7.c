unsigned int invert(unsigned int x, int p, int n)
{
	if (n > p)
		n = p + 1;
	unsigned int mask = ~(~0u << n) << (p - n + 1); // n 1s at position p, rest 0
	return x^mask;
}

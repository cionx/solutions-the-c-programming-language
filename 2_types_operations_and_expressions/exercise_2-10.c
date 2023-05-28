int lower(char c)
{
	if (c >= 'A' && c <= 'Z')
		return c + 'a' - 'A';
	else
		return c;
}


int lower(char c)
{
	return ('A' <= c && c <= 'Z') ? c + 'a' - 'A' : c;
}

int binsearch_new(int x, int v[], int vsize);
int binsearch_old(int x, int v[], int n);

int binsearch_new(int x, int v[], int vsize)
{
	int low, high, mid;
	low = 0;
	high = vsize - 1;
	while (low < high) {
		mid = (low + high) / 2; /* always lower that high */
		if (x > v[mid])
			low = mid + 1; /* strictly increases low */
		else
			high = mid; /* strictly decreases high */
	}
	return (v[low] == x) ? low : -1;
}

int binsearch_old(int x, int v[], int n)
{
	int low, high, mid;
	low = 0;
	high = n - 1;
	while (low <= high) {
		mid = (low + high) / 2;
		if (x < v[mid])
			high = mid - 1;
		else if (x > v[mid])
			low = mid + 1;
		else
			/* found match */
			return mid;
	}
	return -1; /* no match */
}

int main(void)
{
	int v[] = {0,  1,  2,  3,  4,  5,  6,  7,  8,  9,  10, 11, 12, 14, 15,
	           16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30,
	           31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45,
	           46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 58, 59, 60, 70,
	           71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85,
	           86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99};

	int repeat = 1e7;
	for (int i = 0; i < repeat; ++i)
		for (int x = 0; x < 100; ++x)
			binsearch_new(x, v, 100);

	return 0;
}

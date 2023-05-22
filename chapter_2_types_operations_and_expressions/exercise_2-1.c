#include <float.h>
#include <limits.h>
#include <stdio.h>

int main(void) {
	/* VALUES FROM THE HEADER FILES. */

	printf("HEADERS\n");
	printf("-------\n");
	printf("signed char:\n%d\n%d\n", SCHAR_MIN, SCHAR_MAX);
	printf("-------\n");
	printf("unsigned char:\n%u\n%u\n", 0, UCHAR_MAX);
	printf("-------\n");
	printf("signed short:\n%d\n%d\n", SHRT_MIN, SHRT_MAX);
	printf("-------\n");
	printf("unsigned short:\n%d\n%d\n", 0, USHRT_MAX);
	printf("-------\n");
	printf("signed int:\n%d\n%d\n", INT_MIN, INT_MAX);
	printf("-------\n");
	printf("unsigned int:\n%u\n%u\n", 0, UINT_MAX);
	printf("-------\n");
	printf("signed long:\n%ld\n%ld\n", LONG_MIN, LONG_MAX);
	printf("-------\n");
	printf("unsigned long:\n%d\n%llu\n", 0, ULLONG_MAX);
	printf("-------\n");
	printf("float:\n%g\n%f\n", FLT_MIN, FLT_MAX);
	printf("-------\n");
	printf("double:\n%g\n%f\n", DBL_MIN, DBL_MAX);
	printf("-------\n");
	printf("long double:\n%Lg\n%Lf\n", LDBL_MIN, LDBL_MAX);
	printf("-------\n");

	/* COMPUTATIONAL VALUES. */

	printf("\n\n");
	printf("Computation\n");
	printf("-----------\n");

	/* FOR SIGNED CHARS. */
	char char_max = 0;
	char char_add = 1;
	while ((char)(2 * char_add) > char_add) {
		char_add *= 2;
	}
	while (char_add > 0) {
		if ((char)(char_max + char_add) > char_max)
			char_max += char_add;
		char_add /= 2;
	}
	char char_min = 0;
	char char_sub = -1;
	while ((char)(2 * char_sub) < char_sub)
		char_sub *= 2;
	while (char_sub < 0) {
		if ((char)(char_min + char_sub) < char_min)
			char_min += char_sub;
		char_sub /= 2;
	}
	printf("signed char:\n%d\n%d\n", char_min, char_max);
	printf("-----------\n");

	/* FOR UNSIGNED CHARS. */
	unsigned char uchar_max = 0;
	unsigned char uchar_add = 1;
	while ((unsigned char)(2 * uchar_add) > uchar_add) {
		uchar_add *= 2;
	}
	while (uchar_add > 0) {
		if ((unsigned char)(uchar_max + uchar_add) > uchar_max)
			uchar_max += uchar_add;
		uchar_add /= 2;
	}
	printf("unsigned char:\n%u\n%u\n", 0, uchar_max);
	printf("-----------\n");

	/* FOR SIGNED SHORTS. */
	short short_max = 0;
	short short_add = 1;
	while ((short)(2 * short_add) > short_add) {
		short_add *= 2;
	}
	while (short_add > 0) {
		if ((short)(short_max + short_add) > short_max)
			short_max += short_add;
		short_add /= 2;
	}
	short short_min = 0;
	short short_sub = -1;
	while ((short)(2 * short_sub) < short_sub)
		short_sub *= 2;
	while (short_sub < 0) {
		if ((short)(short_min + short_sub) < short_min)
			short_min += short_sub;
		short_sub /= 2;
	}
	printf("signed short:\n%d\n%d\n", short_min, short_max);
	printf("-----------\n");

	/* FOR UNSIGNED SHORTS. */
	unsigned short ushort_max = 0;
	unsigned short ushort_add = 1;
	while ((unsigned short)(2 * ushort_add) > ushort_add) {
		ushort_add *= 2;
	}
	while (ushort_add > 0) {
		if ((unsigned short)(ushort_max + ushort_add) > ushort_max)
			ushort_max += ushort_add;
		ushort_add /= 2;
	}
	printf("unsigned short:\n%d\n%d\n", 0, ushort_max);
	printf("-----------\n");

	/* FOR SIGNED INTS. */
	int int_max = 0;
	int int_add = 1;
	while (2 * int_add > int_add) {
		int_add *= 2;
	}
	while (int_add > 0) {
		if (int_max + int_add > int_max)
			int_max += int_add;
		int_add /= 2;
	}
	int int_min = 0;
	int int_sub = -1;
	while (2 * int_sub < int_sub)
		int_sub *= 2;
	while (int_sub < 0) {
		if (int_min + int_sub < int_min)
			int_min += int_sub;
		int_sub /= 2;
	}
	printf("signed int:\n%d\n%d\n", int_min, int_max);
	printf("-----------\n");

	/* FOR UNSIGNED INTS. */
	unsigned int uint_max = 0;
	unsigned int uint_add = 1;
	while ((unsigned int)(2 * uint_add) > uint_add) {
		uint_add *= 2;
	}
	while (uint_add > 0) {
		if ((unsigned int)(uint_max + uint_add) > uint_max)
			uint_max += uint_add;
		uint_add /= 2;
	}
	printf("unsigned int:\n%u\n%u\n", 0, uint_max);
	printf("-----------\n");

	/* FOR SIGNED LONGS. */
	long long_max = 0;
	long long_add = 1;
	while ((long)(2 * long_add) > long_add) {
		long_add *= 2;
	}
	while (long_add > 0) {
		if ((long)(long_max + long_add) > long_max)
			long_max += long_add;
		long_add /= 2;
	}
	long long_min = 0;
	long long_sub = -1;
	while ((long)(2 * long_sub) < long_sub)
		long_sub *= 2;
	while (long_sub < 0) {
		if ((long)(long_min + long_sub) < long_min)
			long_min += long_sub;
		long_sub /= 2;
	}
	printf("signed long:\n%ld\n%ld\n", long_min, long_max);
	printf("-----------\n");

	/* FOR UNSIGNED LONGS. */
	unsigned long ulong_max = 0;
	unsigned long ulong_add = 1;
	while ((unsigned long)(2 * ulong_add) > ulong_add) {
		ulong_add *= 2;
	}
	while (ulong_add > 0) {
		if ((unsigned long)(ulong_max + ulong_add) > ulong_max)
			ulong_max += ulong_add;
		ulong_add /= 2;
	}
	printf("unsigned long:\n%lu\n%lu\n", 0l, ulong_max);
	printf("-----------\n");

	/* FOR FLOATS */
	float float_max = 1.0;
	while (4 * float_max > 2 * float_max)
		float_max *= 2;
	float_max *= 2;
	float float_eps = 1.0;
	while ((float)(float_eps / 2) > 0)
		float_eps /= 2;
	printf("float:\n%g\n%f\n", float_eps, float_max);
}

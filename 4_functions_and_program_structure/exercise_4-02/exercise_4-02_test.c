#include "exercise_4-02.h"
#include <stdio.h>

int main(void)
{
	char *tests[] = {"123",          "-123",         "0",
	                 "123.456",      "-123.456",     "0.123",
	                 "-0.123",       ".123",         "-.123",
	                 "123e4",        "-123e4",       "0e4",
	                 "123e-4",       "-123e-4",      "0e-4",
	                 "123.456e7",    "-123.456e7",   "123.456e-7",
	                 "-123.456e-7",  "123.456e789",  "-123.456e789",
	                 "0e789",        "123.456e-789", "-123.456e-789",
	                 "1e123456789",  "-1e123456789", "1e-123456789",
	                 "-1e-123456789", "123.456-3", "123.456+3"};
	int testCount = 30;

	for (int i = 0; i < testCount; ++i)
		printf("\"%s\" becomes %g\n", tests[i], my_atof(tests[i]));

	return 0;
}
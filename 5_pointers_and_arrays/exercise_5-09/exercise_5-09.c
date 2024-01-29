#include <stdio.h>

static int daytab[2][13] = {
	{0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}, /* non-leap year */
	{0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}  /* leap year */
};

int day_of_year(int year, int month, int day);
void month_day(int year, int yearday, int *pmonth, int *pday);

/* day_of_year: set day of year from month & day */
int day_of_year(int year, int month, int day)
{
	int i, leap;

	leap = ((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0);
	for (i = 1; i < month; ++i)
		day += *(*(daytab + leap) + i);
	return day;
}

/* month_day: set month, day from day of year */
void month_day(int year, int yearday, int *pmonth, int *pday)
{
	int i, leap;

	leap = ((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0);
	for (i = 1; yearday > *(*(daytab + leap) + i); ++i)
		yearday -= *(*(daytab + leap) + i);
	*pmonth = i;
	*pday = yearday;
}

int main(void)
{
	printf("March 1st 2023 is the %dth day of the year\n",
	       day_of_year(2023, 3, 1));
	printf("March 1st 2024 is the %dth day of the year\n",
	       day_of_year(2024, 3, 1));
	return 0;
}

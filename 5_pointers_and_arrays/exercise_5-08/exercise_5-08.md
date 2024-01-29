# Exercise 5-8

> There is no error checking in `day_of_year` or `month_day.`
> Remedy this defect.

---

We extend `day_of_year` as follows:
```c
int day_of_year(int year, int month, int day)
{
	int i, leap;

	leap = ((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0);

	if (month <= 0 || 12 < month) {
		printf("invalid month\n");
		return -1;
	}
	if (day <= 0 || daytab[leap][month] < day) {
		printf("invalid day\n");
		return -1;
	}

	for (i = 1; i < month; ++i)
		day += daytab[leap][i];
	return day;
}
```

We also add one test to `month_day`:
```c
/* month_day: set month, day from day of year */
void month_day(int year, int yearday, int *pmonth, int *pday)
{
	int i, leap;

	leap = ((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0);

	if (yearday <= 0 || (leap ? 366 : 365) < yearday) {
		printf("invalid day\n");
		*pmonth = -1;
		*pday = -1;
	}

	for (i = 1; yearday > daytab[leap][i]; ++i)
		yearday -= daytab[leap][i];
	*pmonth = i;
	*pday = yearday;
}
```

We have not tested our modified functions.

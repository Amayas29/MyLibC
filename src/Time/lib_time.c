#include <stdio.h>
#include "lib_time.h"

static int leap(int year);
static int number_of_days(int month, int year);
static int first_january(int year);
static int number_day_week(int day, int month, int year);

char *get_day_name(int day, int month, int year) {

	day = number_day_week(day, month, year);
	if(day == 0) return "Saturday";
	if(day == 1) return "Sunday";
	if(day == 2) return "Monday";
	if(day == 3) return "Tuesday";
	if(day == 4) return "Wednesday";
	if(day == 5) return "Thursday";
	if(day == 6) return "Friday";

	return "Invalid day";
}

int main() {

	int day = 29, month = 5, year = 2001;

	printf("%s\n", get_day_name(day, month, year));

	return 0;
}

/* returns 1 if the year is leap year */
static int leap(int year) {

	if((year % 4 == 0 && year % 100 != 0) || year % 400 == 0)
		return 1;
	
	return 0;
}

/* Returns the number of day of a month */
static int number_of_days(int month, int year) {

	if(month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12)
		return 31;

	if(month == 4 || month == 6 || month == 9 || month == 11 )
		return 30;

	return 28 + leap(year);
}

/* Returns the number of the weekday corresponding to January 1 */
static int first_january(int year) {

	int a = 1900, j = 2;

	for(int i = a; i < year; i++)
		j = (j + 1 + leap(i)) % 7;
		
	return j;
}

/* Returns the number of the day of the week corresponding to the day passed in argument */
static int number_day_week(int day, int month, int year) {

	int d = first_january(year);

	for(int m = 1; m < month; m++)
		d = ((d + number_of_days(m, year)) % 7);

	d = (d + day) % 7 - 1;
	return d;
}
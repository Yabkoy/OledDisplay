#include "dateAndTimeValidation.h"

int concat(int x, int y) {
	if(y==0){
        return x*10;
    }
    int temp = y;
    while (y != 0) {
        x *= 10;
        y /= 10;
    }
    return x + temp;
}

bool isLeapYear(uint8_t year){
    return (year%4 == 0 && year%100 != 0) || year%400 == 0;
}

bool isMonthHave31Days(uint8_t month){
    return month< 8? month%2 : !(month%2);
}

void validateTimeUnits(uint8_t* timeUnit, uint8_t min, uint8_t max){
	if(*timeUnit > max || *timeUnit < min){
		*timeUnit = min;
	}
}
void validateYear(uint16_t* year, uint16_t min, uint16_t max){
	if(*year > max || *year < min){
		*year = min;
	}
}

void validateDayOfMonth(uint8_t* day, uint8_t month, uint16_t year){
	if(month == 2){
		if(isLeapYear(year)){
			validateTimeUnits(day, 1, 29);
		} else{
			validateTimeUnits(day, 1, 28);
		}
		return;
	} 
	validateTimeUnits(day, 1, 30+isMonthHave31Days(month));
}

//Algorithm from: "https://www.geeksforgeeks.org/find-day-of-the-week-for-a-given-date/"
int getDayOfWeek(int d, int m, int y)
{
    static int t[] = { 0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4 };
    y -= m < 3;
    return (y + y / 4 - y / 100 + y / 400 + t[m - 1] + d)
           % 7;
}
void setCorrectDayOfWeek(ds3231_datetime_t* dateTime){
	printf("DAY: %d, MON: %d, YEAR: %d\n", dateTime->day, dateTime->month, dateTime->year);
	uint8_t dowIndex = getDayOfWeek(dateTime->day, dateTime->month, dateTime->year);
	dowIndex = (dowIndex == 0)? 6 : dowIndex-1;
	dateTime->dotw = dowIndex;
}

void validateDateTime(ds3231_datetime_t* dateTime){
	validateTimeUnits(&dateTime->hour, 0, 23);
	validateTimeUnits(&dateTime->minutes, 0, 59);
	validateTimeUnits(&dateTime->seconds, 0, 59);
	validateTimeUnits(&dateTime->month, 1, 12);
	validateTimeUnits(&dateTime->dotw, 0, 6);
	validateYear(&dateTime->year, 2000, 2099);
	validateDayOfMonth(&dateTime->day, dateTime->month, dateTime->year);
}
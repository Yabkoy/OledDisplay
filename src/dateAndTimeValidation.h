#ifndef DATE_TIME_VALIDATION
#define DATE_TIME_VALIDATION
#include "driver/ds3231.h"


int concat(int x, int y);
bool isLeapYear(uint8_t year);
bool isMonthHave31Days(uint8_t month);
void validateTimeUnits(uint8_t* timeUnit, uint8_t min, uint8_t max);

void validateYear(uint16_t* year, uint16_t min, uint16_t max);
void validateDayOfMonth(uint8_t* day, uint8_t month, uint16_t year);
int getDayOfWeek(int d, int m, int y);
void setCorrectDayOfWeek(ds3231_datetime_t* dateTime);
void validateDateTime(ds3231_datetime_t* dateTime);

#endif
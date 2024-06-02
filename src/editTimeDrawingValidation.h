#ifndef EDIT_TIME_DRAWING_VALIDATION_H
#define EDIT_TIME_DRAWING_VALIDATION_H
#include "dateAndTimeValidation.h"
#include "driver/ds3231.h"
 
 typedef struct{
	uint8_t h1;
	uint8_t h2;
	uint8_t m1;
	uint8_t m2;
} editClockNumbers;

void initEditClockNumbersData(editClockNumbers* ecn, ds3231_rtc_t* rtc);
void validateEditClockNumber(editClockNumbers* ecn);

#endif
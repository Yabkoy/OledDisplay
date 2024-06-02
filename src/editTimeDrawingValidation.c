#include "editTimeDrawingValidation.h"

void initEditClockNumbersData(editClockNumbers* ecn, ds3231_rtc_t* rtc){
	ds3231_datetime_t ecnTime;
	ds3231_get_datetime(&ecnTime, rtc);

	ecn->h1 = ecnTime.hour/10;
	ecn->h2 = ecnTime.hour%10;
	ecn->m1 = ecnTime.minutes/10;
	ecn->m2 = ecnTime.minutes%10;
}

void validateEditClockNumber(editClockNumbers* ecn){
	validateTimeUnits(&ecn->h1, 0, 2);
	if(ecn->h1 > 1){
		validateTimeUnits(&ecn->h2, 0, 3);
	}else{
		validateTimeUnits(&ecn->h2, 0, 9);
	}
	validateTimeUnits(&ecn->m1, 0, 5);
	validateTimeUnits(&ecn->m2, 0, 9);
}
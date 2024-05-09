#include "programLoop.h"

uint validateHour(uint hour){
	return (hour <= 23)? hour : 0;
}

uint validateMinute(uint minute){
	return (minute <= 59)? minute : 0;
}

void addHoursAndMinutesToRTCModule(ds3231_rtc_t* rtcModule, ds3231_datetime_t* currentTime, uint hourPin, uint minutePin){
	uint vHour = validateHour(currentTime->hour + !gpio_get(hourPin));
	uint vMinute = validateMinute(currentTime->minutes + !gpio_get(minutePin));

	ds3231_datetime_t newTime = {
		.hour = vHour,
		.minutes = vMinute,
	};

	ds3231_set_datetime(&newTime, rtcModule);
}

size_t* getCurrentTimeDigits(ds3231_datetime_t* currentTime){
	size_t* numberIndexData = (size_t*)malloc(sizeof(size_t)*4);

	numberIndexData[0] = currentTime->hour/10;
	numberIndexData[1] = currentTime->hour%10; 
	numberIndexData[2] = currentTime->minutes/10;
	numberIndexData[3] = currentTime->minutes%10;

	return numberIndexData;
}
void drawNumbers(displayBuffer* oledDisplay, ds3231_datetime_t* currentTime){
	for(size_t i=0; i<4; i++){
		size_t* currentTimeDigits = getCurrentTimeDigits(currentTime);
		uint8_t* scaleNumber = scaleImageNearestNeighbor(allNumbersPointer[currentTimeDigits[i]], 10, 14, 4);
		uint8_t distanceFromLeft = (i>1)? 25 : 5;
		addUint8TBufferToDisplay(oledDisplay, scaleNumber, 10*4, 14*4, (i*12*4)+distanceFromLeft, 4);
		
		free(scaleNumber);
		free(currentTimeDigits);
	}
}

void drawClockDots(displayBuffer* oledDisplay){
	for(int i=0; i<2; i++){
		uint8_t* dot = (uint8_t*)malloc(8*8);
		memset(dot, 0xFF, 8*8);
		addUint8TBufferToDisplay(oledDisplay, dot, 8, 8, 104, (i*21)+20);
		free(dot);
	}
}
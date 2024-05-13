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

	currentTime->hour = vHour;
	currentTime->minutes = vMinute;

	ds3231_datetime_t newTime = {
		.hour = vHour,
		.minutes = vMinute,
		.dotw = currentTime->dotw,
		.day = currentTime->day,
		.month = currentTime->month,
		.year = currentTime->year
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

size_t* getCurrentDateDigits(ds3231_datetime_t* currentTime){
	size_t* numberIndexData = (size_t*)malloc(sizeof(size_t)*8);

	numberIndexData[0] = currentTime->day/10;
	numberIndexData[1] = currentTime->day%10;
	numberIndexData[2] = currentTime->month/10;
	numberIndexData[3] = currentTime->month%10;
	numberIndexData[4] = (currentTime->year)/1000;
	numberIndexData[5] = ((currentTime->year)/100)%10;
	numberIndexData[6] = ((currentTime->year)%100)/10;
	numberIndexData[7] = ((currentTime->year)%100)%10;

	return numberIndexData;
}

uint8_t calculateLeftDistanceForDate(size_t index, size_t scale){
	uint8_t scaleValue = index*14*scale;
	uint8_t conditionValue = (index<6)? (!(index%2)*5)+25 : (-5*(index-5))+25;
	return scaleValue+conditionValue;
}

uint8_t calculateLeftDistanceForTime(size_t index, size_t scale){

	uint8_t scaleValue = index*12*scale;
	uint8_t conditionValue = (index>1)? 25 : 5;
	return scaleValue+conditionValue;
}

void drawNumbers(displayBuffer* oledDisplay, ds3231_datetime_t* currentTime, size_t iterations, uint8_t heightDraw, size_t scale, size_t* (*currentDigitsFunction)(ds3231_datetime_t*), uint8_t (*calculateLeftDistanceFunction)(size_t, size_t)){
	uint8_t width = 10;
	uint8_t height = 14;

	for(size_t i=0; i<iterations; i++){
		size_t* digitsPointer = currentDigitsFunction(currentTime);
		uint8_t* scaleNumber = scaleImageNearestNeighbor(allNumbersPointer[digitsPointer[i]], width, height, scale);
		uint8_t distanceFromLeft = calculateLeftDistanceFunction(i, scale);
		addUint8TBufferToDisplay(oledDisplay, scaleNumber, width*scale, height*scale, distanceFromLeft, heightDraw);
		
		free(scaleNumber);
		free(digitsPointer);
	}	
}

void drawCurrentDateNumbers(displayBuffer* oledDisplay, ds3231_datetime_t* currentTime){
	drawNumbers(oledDisplay, currentTime, 8, 18, 2, getCurrentDateDigits, calculateLeftDistanceForDate);
}

void drawCurrentTimeNumbers(displayBuffer* oledDisplay, ds3231_datetime_t* currentTime){
	drawNumbers(oledDisplay, currentTime, 4, 4, 4, getCurrentTimeDigits, calculateLeftDistanceForTime);
}

void drawSecondsNumbers(displayBuffer* oledDisplay, ds3231_datetime_t* currentTime){
	size_t secLeftDigit = currentTime->seconds/10;
	size_t secRightDigit = currentTime->seconds%10;
	addUint8TBufferToDisplay(oledDisplay, allNumbersPointer[secLeftDigit], 10, 14, 256-32, 27);
	addUint8TBufferToDisplay(oledDisplay, allNumbersPointer[secRightDigit], 10, 14, 256-20, 27);
}

void drawDotToDisplay(displayBuffer* oledDisplay, size_t width, size_t height, uint8_t x, uint8_t y){
	uint8_t* dot = (uint8_t*)malloc(width*height);
	memset(dot, 0xFF, width*height);
	addUint8TBufferToDisplay(oledDisplay, dot, width, height, x, y);
	free(dot);
}

void drawAllDots(displayBuffer* oledDisplay){
	for(int i=0; i<2; i++){
		drawDotToDisplay(oledDisplay, 8, 8, 104, (i*21)+20);
	}
	for(int i=0; i<2; i++){
		drawDotToDisplay(oledDisplay, 3, 3, 256-39, (i*5)+29);
	}
}

void drawDayOfWeek(displayBuffer* oledDisplay, ds3231_datetime_t* currentTime){
	uint8_t dayOfWeekIndex = currentTime->dotw;
	addUint8TBufferToDisplay(oledDisplay, allDaysPointer[dayOfWeekIndex], 34, 14, 256-41, 45);
}

void drawTemperature(displayBuffer* oledDisplay, ds3231_rtc_t* rtc){
	float currentTemp;
	ds3231_get_temperature(&currentTemp, rtc);
	size_t tempFirstDigit = (int)currentTemp/10;
	size_t tempSecDigit = (int)currentTemp%10;


	addUint8TBufferToDisplay(oledDisplay, allNumbersPointer[tempFirstDigit], 10, 14, 256-41, 8);
	addUint8TBufferToDisplay(oledDisplay, allNumbersPointer[tempSecDigit], 10, 14, 256-29, 8);
	addUint8TBufferToDisplay(oledDisplay, fontCelsius, 17, 14, 256-17, 8);
}
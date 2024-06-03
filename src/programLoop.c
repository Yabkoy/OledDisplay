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

void drawRectangleToDisplay(displayBuffer* oledDisplay, size_t width, size_t height, uint8_t x, uint8_t y){
	uint8_t* dot = (uint8_t*)malloc(width*height);
	memset(dot, 0xFF, width*height);
	addUint8TBufferToDisplay(oledDisplay, dot, width, height, x, y);
	free(dot);
}

void drawFullScaleData(SH1122_SPI* spiData, const uint8_t* data, size_t dimmLevel){
	displayBuffer fullScaleDisplay;
	initDisplayBuffer(&fullScaleDisplay, 256, 64);
	addUint8TBufferToDisplay(&fullScaleDisplay, data, 256, 64, 0, 0);
	dimBufferFromTopAndBottom(&fullScaleDisplay, dimmLevel);
	convertNormalDisplayBufferToOledBuffer(&fullScaleDisplay);
	
	sh1122_show(spiData, fullScaleDisplay.buffer, fullScaleDisplay.bufferLen);
	deAllocBuffer(&fullScaleDisplay);

}

void drawEditModeMessage(SH1122_SPI* spiData, size_t dimmLevel){
	drawFullScaleData(spiData, editModeMessage, dimmLevel);
}

void drawClockModeMessage(SH1122_SPI* spiData, size_t dimmLevel){
	drawFullScaleData(spiData, clockModeMessage, dimmLevel);
}

void drawMazdaLogo(SH1122_SPI* spiData, uint8_t y, size_t dimmLevel){
	displayBuffer logoDisplay;
	initDisplayBuffer(&logoDisplay, 256, 64);
	fillBufferWithValue(&logoDisplay, 0);
	uint8_t* mazdaLogo = (uint8_t*)malloc(76*64);
	uint8_t* mazdaText = (uint8_t*)malloc(174*64);
	memcpy(mazdaLogo, mazdaLogoBitmap, 76*64);
	memcpy(mazdaText, mazdaTextBitmap, 174*64);

	addUint8TBufferToDisplay(&logoDisplay, mazdaLogo, 76, 64, 0, y);
	addUint8TBufferToDisplay(&logoDisplay, mazdaText, 174, 64, 84, y);
	
	if(dimmLevel){
		dimBufferFromTopAndBottom(&logoDisplay, dimmLevel);
	}

	convertNormalDisplayBufferToOledBuffer(&logoDisplay);
	
	deAllocBuffer(&logoDisplay);
	free(mazdaLogo);
	free(mazdaText);
	
	sh1122_show(spiData, logoDisplay.buffer, logoDisplay.bufferLen);
}

void drawTimeDots(displayBuffer* oledDisplay){
	for(int i=0; i<2; i++){
		drawRectangleToDisplay(oledDisplay, 8, 8, 104, (i*21)+20);
	}
}

void drawSecondDots(displayBuffer* oledDisplay){
	for(int i=0; i<2; i++){
		drawRectangleToDisplay(oledDisplay, 3, 3, 256-39, (i*5)+29);
	}
}

void drawDateDots(displayBuffer* oledDisplay){
	for(int i=0; i<2; i++){
		drawRectangleToDisplay(oledDisplay, 5, 5, calculateLeftDistanceForDate((i+1)*2, 2)-9, 41);
	}
}

void drawUnderlineInEditNumbers(displayBuffer* oledDisplay, size_t index, size_t scale){
	drawRectangleToDisplay(oledDisplay, 10*scale, 2, calculateLeftDistanceForEditTime(index, scale), 62);
}
void drawUnderlineInEditDate(displayBuffer* oledDisplay, size_t index, size_t scale){
	drawRectangleToDisplay(oledDisplay, 10*scale, 2, calculateLeftDistanceForDate(index, scale), 50);
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
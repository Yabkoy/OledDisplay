#include "mainDrawingElements.h"

void drawClockModeNumbers(SH1122_SPI* spiData, ds3231_rtc_t* rtc, bool isDot, size_t dimmLevel, size_t invertLevel){
	displayBuffer oledDisplay;
	initDisplayBuffer(&oledDisplay, 256, 64);

	ds3231_datetime_t currentTime;
	ds3231_get_datetime(&currentTime, rtc);

	if(isDot){
		drawTimeDots(&oledDisplay);
		drawSecondDots(&oledDisplay);
	}
	drawCurrentTimeNumbers(&oledDisplay, &currentTime);
	drawTemperature(&oledDisplay, rtc);
	drawSecondsNumbers(&oledDisplay, &currentTime);
	drawDayOfWeek(&oledDisplay, &currentTime);

	if(invertLevel){
		invertDisplayBufferData(&oledDisplay, invertLevel);
	}
	convertNormalDisplayBufferToOledBuffer(&oledDisplay);
	
	if(dimmLevel){
		dimBufferFromTopAndBottom(&oledDisplay, dimmLevel);
	}


	sh1122_show(spiData, oledDisplay.buffer, oledDisplay.bufferLen);

	deAllocBuffer(&oledDisplay);
}

void drawDateModeNumbers(SH1122_SPI* spiData, ds3231_rtc_t* rtc, bool isDot, size_t dimmLevel, size_t invertLevel){
	displayBuffer oledDisplay;
	initDisplayBuffer(&oledDisplay, 256, 64);
	ds3231_datetime_t currentTime;
	ds3231_get_datetime(&currentTime, rtc);
	drawCurrentDateNumbers(&oledDisplay, &currentTime);
	if(isDot){
		drawDateDots(&oledDisplay);
	}

	if(dimmLevel){
		dimBufferFromTopAndBottom(&oledDisplay, dimmLevel);
	}
    if(invertLevel){
		invertDisplayBufferData(&oledDisplay, invertLevel);
    }
	convertNormalDisplayBufferToOledBuffer(&oledDisplay);
	sh1122_show(spiData, oledDisplay.buffer, oledDisplay.bufferLen);
	deAllocBuffer(&oledDisplay);
}

void drawEditClockModeNumbers(SH1122_SPI* spiData, ds3231_rtc_t* rtc, editClockNumbers* editNumbers, bool* editMode, size_t dimmLevel){
	displayBuffer oledDisplay;
	initDisplayBuffer(&oledDisplay, 256, 64);
    static uint8_t currentEditIndex = 0;

	if(isButtonPressed(BTN2_PIN)){

		switch (currentEditIndex)
		{
			case 0:
				editNumbers->h1 = (editNumbers->h1+1)%10;
				break;

			case 1:{
				editNumbers->h2 = (editNumbers->h2+1)%10;
				break;
			}
			case 2:{
				editNumbers->m1 = (editNumbers->m1+1)%10;
				break;
			}
			case 3:{
				editNumbers->m2 = (editNumbers->m2+1)%10;
				break;
			}
			case 4:{
				editNumbers->year++;
				break;
			}
			case 5:{
				editNumbers->month++;
				break;
			}
			case 6:{
				editNumbers->day++;
			}
		}
		sleep_ms(75);
	}

	validateEditClockNumber(editNumbers);
	validateEditDateNumber(editNumbers);

	ds3231_datetime_t currentTime = {
		.hour = concat(editNumbers->h1, editNumbers->h2),
		.minutes = concat(editNumbers->m1, editNumbers->m2),
		.day = editNumbers->day,
		.month = editNumbers->month,
		.year = editNumbers->year,
	};

	if(isButtonPressed(BTN1_PIN)){
		currentEditIndex++;
		sleep_ms(175);
	}
	if(currentEditIndex >= 7){
		setCorrectDayOfWeek(&currentTime);
		ds3231_set_datetime(&currentTime, rtc);
		*editMode = 0;
		currentEditIndex = 0;
		for(uint8_t i=0; i<=32; i++){
            drawDateModeNumbers(spiData, rtc, 1, i, 0);
        }
		for(uint8_t i=32; i>0; i--){
			drawClockModeMessage(spiData, i);
		}
		sleep_ms(1500);
		for(uint8_t i=0; i<=32; i++){
			drawClockModeMessage(spiData, i);
			sleep_ms(15);
		}
		for(uint8_t i=32; i>0; i--){
			drawClockModeNumbers(spiData, rtc, 0, i, 0);
		}
		return;
	}
	if(currentEditIndex < 4){
		drawCurrentEditTimeNumbers(&oledDisplay, &currentTime);
		drawUnderlineInEditNumbers(&oledDisplay, currentEditIndex, 4);
	} else{
		drawCurrentDateNumbers(&oledDisplay, &currentTime);
		drawDateDots(&oledDisplay);
		drawUnderlineInEditDate(&oledDisplay, 4-((currentEditIndex-4)*2), 2);
	}

	if(dimmLevel){
		dimBufferFromTopAndBottom(&oledDisplay, dimmLevel);
	}

	convertNormalDisplayBufferToOledBuffer(&oledDisplay);
	sh1122_show(spiData, oledDisplay.buffer, oledDisplay.bufferLen);

	deAllocBuffer(&oledDisplay);
}

void playIntroAnimation(SH1122_SPI* spiData, ds3231_rtc_t* rtc){
	for(uint8_t i=64; i>0; i--){
		drawMazdaLogo(spiData, i, 0);
		sleep_ms(10);

	}
	sleep_ms(2000);
	for(uint8_t i=0; i<=32; i++){
		drawMazdaLogo(spiData, 1, i);
	}

	for(uint8_t i=32; i>0; i--){
		drawClockModeNumbers(spiData, rtc, 0, i, 0);
	}
}
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "pico/stdlib.h"
#include "pico/time.h"
#include "hardware/gpio.h"

#include "moduleInitialization.h"
#include "programLoop.h"
#include "displayBuffer.h"

#define HOURS_BUTTON_PIN  17
#define MINUTE_BUTTON_PIN 16


uint32_t getRunningTime(){
	return to_ms_since_boot(get_absolute_time());
}

bool isAnyTimeChangeButtonPressed(uint hourButton, uint minuteButton){
	return !gpio_get(hourButton) || !gpio_get(minuteButton);
}

int main(){
	///STARTING FUNCTION HANDLE

	setup_default_uart();
	printf("RaspiStart\n\n");

	ds3231_rtc_t rtc;
	SH1122_SPI spiData;

	initMainModules(&rtc, &spiData);
	initButton(MINUTE_BUTTON_PIN);
	initButton(HOURS_BUTTON_PIN);


	///PROGRAM LOOP HANDLE
	bool isDot = true;

	uint32_t previousTimeSecound = 0;

	while(true){
		if(isAnyTimeChangeButtonPressed(HOURS_BUTTON_PIN, MINUTE_BUTTON_PIN)){
				ds3231_datetime_t currentTime;
				ds3231_get_datetime(&currentTime, &rtc);
				addHoursAndMinutesToRTCModule(&rtc, &currentTime, HOURS_BUTTON_PIN, MINUTE_BUTTON_PIN);

				ds3231_get_datetime(&currentTime, &rtc);

				displayBuffer oledDisplay;
				initDisplayBuffer(&oledDisplay, 256, 64);
				drawNumbers(&oledDisplay, &currentTime);
				convertNormalDisplayBufferToOledBuffer(&oledDisplay);
				sh1122_show(&spiData, oledDisplay.buffer, oledDisplay.bufferLen);

				deAllocBuffer(&oledDisplay);
				sleep_ms(100);
			}


		if(getRunningTime() - previousTimeSecound >= 1000){
			displayBuffer oledDisplay;
			initDisplayBuffer(&oledDisplay, 256, 64);

			ds3231_datetime_t currentTime;
			ds3231_get_datetime(&currentTime, &rtc);
			
			if(isDot){
				drawClockDots(&oledDisplay);
			}
			drawNumbers(&oledDisplay, &currentTime);

			convertNormalDisplayBufferToOledBuffer(&oledDisplay);
			sh1122_show(&spiData, oledDisplay.buffer, oledDisplay.bufferLen);

			deAllocBuffer(&oledDisplay);

			isDot = !isDot;
			previousTimeSecound = getRunningTime();
		}
	}

}

#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "pico/stdlib.h"
#include "pico/time.h"
#include "hardware/gpio.h"

#include "scaling.h"
#include "font.h"
#include "moduleInitialization.h"
#include "displayBuffer.h"

#define HOURS_BUTTON_PIN  17
#define MINUTE_BUTTON_PIN 16


uint32_t getRunningTime(){
	return to_ms_since_boot(get_absolute_time());
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
	while(true){
		displayBuffer oledDisplay;
		initDisplayBuffer(&oledDisplay, 256, 64);

		ds3231_datetime_t currentTime;
		ds3231_get_datetime(&currentTime, &rtc);

		if(!gpio_get(HOURS_BUTTON_PIN) || !gpio_get(MINUTE_BUTTON_PIN)){
			ds3231_datetime_t newTime = {
				.hour = currentTime.hour + !gpio_get(HOURS_BUTTON_PIN),
				.minutes = currentTime.minutes + !gpio_get(MINUTE_BUTTON_PIN),
			};

			ds3231_set_datetime(&newTime, &rtc);
		}



		size_t numbersIndexData[] = {
			currentTime.hour/10, 
			currentTime.hour%10, 
			currentTime.minutes/10, 
			currentTime.minutes%10
		};

		for(size_t i=0; i<4; i++){
			uint8_t* scaleNumber = scaleImageNearestNeighbor(allNumbersPointer[numbersIndexData[i]], 10, 14, 4);
			uint8_t distanceFromLeft = (i>1)? 50 : 30;
			addUint8TBufferToDisplay(&oledDisplay, scaleNumber, 10*4, 14*4, (i*12*4)+distanceFromLeft, 4);
			free(scaleNumber);
		}
		if(isDot){
			for(int i=0; i<2; i++){
				uint8_t* dot = (uint8_t*)malloc(8*8);
				memset(dot, 0xFF, 8*8);
				addUint8TBufferToDisplay(&oledDisplay, dot, 8, 8, 128, (i*21)+20);
				free(dot);
			}
		}


		convertNormalDisplayBufferToOledBuffer(&oledDisplay);
		sh1122_show(&spiData, oledDisplay.buffer, oledDisplay.bufferLen);


		deAllocBuffer(&oledDisplay);

		isDot = !isDot;
		sleep_ms(1000);
	}

}

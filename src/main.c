#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "pico/stdlib.h"
#include "pico/time.h"
#include "scaling.h"
#include "driver/sh1122.h"
#include "driver/ds3231.h"
#include "displayBuffer.h"
#include "font.h"

#define WIDTH 256
#define HEIGHT 64

#define SPI_PORT spi0
#define SPI_RATE 10485760

#define SCLK 18
#define MOSI 19

#define RES 3
#define DC  4
#define CS  5

#define DS3231_I2C_PORT i2c0
#define DS3231_SDA 20 //On board its D
#define DS3231_SCL 21 //On board its C


uint32_t getRunningTime(){
	return to_ms_since_boot(get_absolute_time());
}

int main(){
	setup_default_uart();
	printf("RaspiStart\n\n");

	ds3231_rtc_t rtc;
    ds3231_init(DS3231_I2C_PORT, DS3231_SDA, DS3231_SCL, &rtc);

	SH1122_SPI spiData;
	spiData.width = WIDTH;
	spiData.height = HEIGHT;
	spiData.rate = SPI_RATE;
	spiData.spi = SPI_PORT;
	
	spiData.pin_sclk = SCLK;
	spiData.pin_mosi = MOSI;
	spiData.pin_res = RES;
	spiData.pin_dc = DC;
	spiData.pin_cs = CS;
	
	sh1122_init_pins(&spiData);
	sh1122_init_data(&spiData);



	bool isDot = true;
	while(true){
		displayBuffer oledDisplay;
		initDisplayBuffer(&oledDisplay, 256, 64);

		ds3231_datetime_t currentTime;
		ds3231_get_datetime(&currentTime, &rtc);

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

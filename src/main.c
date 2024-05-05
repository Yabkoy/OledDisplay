#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "pico/stdlib.h"
#include "pico/time.h"
#include "driver/sh1122.h"
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

uint32_t getRunningTime(){
	return to_ms_since_boot(get_absolute_time());
}

uint8_t nearestNeighboruint8_terpolation(const uint8_t* buffer, uint8_t width, uint8_t x, uint8_t y) {
    return buffer[y * width + x];
}


uint8_t* scaleImage(const uint8_t* buffer, uint8_t width, uint8_t height, uint8_t scale) {
    uint8_t newWidth = width*scale;
    uint8_t newHeight = height*scale;
    
    uint8_t* scaledBuffer = (uint8_t*)malloc((newWidth * newHeight)*sizeof(uint8_t));

    float xRatio = (float)width / newWidth;
    float yRatio = (float)height / newHeight;

    for (uint8_t i = 0; i < newHeight; ++i) {
        for (uint8_t j = 0; j < newWidth; ++j) {
            float originalX = j * xRatio;
            float originalY = i * yRatio;

            scaledBuffer[i * newWidth + j] = nearestNeighboruint8_terpolation(buffer, width, originalX, originalY);
        }
    }

    return scaledBuffer;
}

void addNumberToDisplay(displayBuffer* dBuffer, const uint8_t* number, uint8_t w, uint8_t h, uint8_t left){
	for(int i=0; i<h; i++){
		for(int j=0; j<w; j++){
			dBuffer->buffer[((i*256)+j)+left] = number[((i*w)+j)];
		}
	}
}

int main(){
	setup_default_uart();
	printf("RaspiStart\n\n");

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



	//uint8_t* zeroData = scaleImage(fontDataOne, 10, 14, 4);
	size_t currentNumber = 0;
	while(true){
		displayBuffer oledDisplay;
		initDisplayBuffer(&oledDisplay, 256, 64);
		uint8_t* biggerNumber = scaleImage(allNumbersPointer[currentNumber], 10, 14, 4);
		addNumberToDisplay(&oledDisplay, biggerNumber, 10*4, 14*4, 0);
		convertNormalDisplayBufferToOledBuffer(&oledDisplay);
		sh1122_show(&spiData, oledDisplay.buffer, oledDisplay.bufferLen);

		deAllocBuffer(&oledDisplay);
		free(biggerNumber);

		if(currentNumber < 9){
			currentNumber++;
		} else {currentNumber = 0;}

		sleep_ms(100);
	}


}

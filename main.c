#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "pico/stdlib.h"
#include "driver/sh1122.h"
#include "displayBuffer.h"

#define WIDTH 256
#define HEIGHT 64

#define SPI_PORT spi0
#define SPI_RATE 10485760

#define SCLK 18
#define MOSI 19

#define RES 3
#define DC  4
#define CS  5


int main(){
	setup_default_uart();
	printf("RaspiStart");

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
	
	sh1122_Init_Pins(&spiData);
	sh1122_Init_Data(&spiData);




}

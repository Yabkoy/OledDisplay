#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "pico/stdlib.h"
#include "pico/time.h"
#include "driver/sh1122.h"
#include "driver/ds3231.h"
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

}

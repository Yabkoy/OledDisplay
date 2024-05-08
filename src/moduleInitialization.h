#ifndef MODULE_INITIALIZATION_H
#define MODULE_INITIALIZATION_H

#include "driver/sh1122.h"
#include "driver/ds3231.h"

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

void initRTCModule(ds3231_rtc_t* rtc);
void initSpiData(SH1122_SPI* oledSPI);
void initButton(uint pin);

void initMainModules(ds3231_rtc_t* rtc, SH1122_SPI* oledSPI);

#endif
#ifndef MODULE_INITIALIZATION_H
#define MODULE_INITIALIZATION_H

#include "driver/sh1122.h"
#include "driver/ds3231.h"

void initRTCModule(ds3231_rtc_t* rtc);
void initSpiData(SH1122_SPI* oledSPI);
void initButton(uint pin);

void initMainModules(ds3231_rtc_t* rtc, SH1122_SPI* oledSPI);

#endif
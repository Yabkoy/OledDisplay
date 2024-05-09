#ifndef PROGRAM_LOOP_H
#define PROGRAM_LOOP_H

#include "driver/sh1122.h"
#include "driver/ds3231.h"
#include "displayBuffer.h"
#include "scaling.h"
#include "bitmapsData.h"

uint validateHour(uint hour);
uint validateMinute(uint minute);
void addHoursAndMinutesToRTCModule(ds3231_rtc_t* rtcModule, ds3231_datetime_t* currentTime, uint hourPin, uint minutePin);

size_t* getCurrentTimeDigits(ds3231_datetime_t* currentTime);

void drawNumbers(displayBuffer* oledDisplay, ds3231_datetime_t* currentTime);
void drawClockDots(displayBuffer* oledDisplay);

#endif
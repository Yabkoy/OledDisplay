#ifndef PROGRAM_LOOP_H
#define PROGRAM_LOOP_H

#include "driver/sh1122.h"
#include "driver/ds3231.h"
#include "numberDrawing.h"

uint validateHour(uint hour);
uint validateMinute(uint minute);
void addHoursAndMinutesToRTCModule(ds3231_rtc_t* rtcModule, ds3231_datetime_t* currentTime, uint hourPin, uint minutePin);

void drawRectangleToDisplay(displayBuffer* oledDisplay, size_t width, size_t height, uint8_t x, uint8_t y);

void drawFullScaleData(SH1122_SPI* spiData, const uint8_t* data, size_t dimmLevel);
void drawEditModeMessage(SH1122_SPI* spiData, size_t dimmLevel);
void drawClockModeMessage(SH1122_SPI* spiData, size_t dimmLevel);

void drawTimeDots(displayBuffer* oledDisplay);
void drawSecondDots(displayBuffer* oledDisplay);
void drawDateDots(displayBuffer* oledDisplay);
void drawUnderlineInEditNumbers(displayBuffer* oledDisplay, size_t index, size_t scale);
void drawUnderlineInEditDate(displayBuffer* oledDisplay, size_t index, size_t scale);

void drawDayOfWeek(displayBuffer* oledDisplay, ds3231_datetime_t* currentTime);
void drawTemperature(displayBuffer* oledDisplay, ds3231_rtc_t* rtc);

#endif
#ifndef NUMBER_DRAWING_H
#define NUMBER_DRAWING_H
#include "driver/ds3231.h"
#include "displayBuffer.h"
#include "scaling.h"
#include "bitmapsData.h"

size_t* getCurrentTimeDigits(ds3231_datetime_t* currentTime);
size_t* getCurrentDateDigits(ds3231_datetime_t* currentTime);

uint8_t calculateLeftDistanceForDate(size_t index, size_t scale);
uint8_t calculateLeftDistanceForTime(size_t index, size_t scale);
uint8_t calculateLeftDistanceForEditTime(size_t index, size_t scale);

void drawNumbers(displayBuffer* oledDisplay, ds3231_datetime_t* currentTime, size_t iterations, uint8_t heightDraw, size_t scale, size_t* (*currentDigitsFunction)(ds3231_datetime_t*), uint8_t (*calculateLeftDistanceFunction)(size_t, size_t));
void drawCurrentDateNumbers(displayBuffer* oledDisplay, ds3231_datetime_t* currentTime);
void drawCurrentTimeNumbers(displayBuffer* oledDisplay, ds3231_datetime_t* currentTime);
void drawCurrentEditTimeNumbers(displayBuffer* oledDisplay, ds3231_datetime_t* currentTime);
void drawSecondsNumbers(displayBuffer* oledDisplay, ds3231_datetime_t* currentTime);

#endif
#ifndef MAIN_DRAWING_ELEMENTS
#define MAIN_DRAWING_ELEMENTS
#include "programLoop.h"
#include "editTimeDrawingValidation.h"

void drawClockModeNumbers(SH1122_SPI* spiData, ds3231_rtc_t* rtc, bool isDot, size_t dimmLevel, size_t invertLevel);
void drawDateModeNumbers(SH1122_SPI* spiData, ds3231_rtc_t* rtc, bool isDot, size_t dimmLevel);
void drawEditClockModeNumbers(SH1122_SPI* spiData, ds3231_rtc_t* rtc, editClockNumbers* editNumbers, bool* editMode, size_t dimmLevel);
void playIntroAnimation(SH1122_SPI* spiData, ds3231_rtc_t* rtc);

#endif
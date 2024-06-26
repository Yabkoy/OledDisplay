#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "pico/stdlib.h"
#include "pico/time.h"
#include "hardware/gpio.h"

#include "mainDrawingElements.h"
#include "moduleInitialization.h"
#include "displayBuffer.h"
#include "editTimeDrawingValidation.h"
#include "dateAndTimeValidation.h"
 
bool editMode = false;
bool dateMode = false;


int main(){
	///STARTING FUNCTION HANDLE

	setup_default_uart();
	printf("RaspiStart\n\n");

	ds3231_rtc_t rtc;
	SH1122_SPI spiData;

	initMainModules(&rtc, &spiData);
	initButton(BTN1_PIN);
	initButton(BTN2_PIN);

	///INTRO ANIMATION
	#ifdef INTRO_ANIMATION
		playIntroAnimation(&spiData, &rtc);	
	#endif

	///PROGRAM LOOP HANDLE

	uint32_t previousTimeSecound = 0;
	uint32_t previousTimeDot = 0;
	uint32_t previousDateSecound = 0;
	uint32_t previousInvertSecound = 0;

	editClockNumbers editNumbers;
	initEditClockNumbersData(&editNumbers, &rtc);

	bool isDot = true;
	uint8_t isInvert = false;
	uint32_t editSwitchTimeout = 0;
	const uint32_t editSwitchDuration = 100000;

	while(true){
		if(isButtonPressed(BTN1_PIN) && !editMode){
			editSwitchTimeout++;
			if(editSwitchTimeout > editSwitchDuration){
				for(uint8_t i=0; i<=32; i++){
					drawClockModeNumbers(&spiData, &rtc, 0, i, 256);
				}
				for(uint8_t i=32; i>0; i--){
					drawEditModeMessage(&spiData, i);
				}
				sleep_ms(1000);
				for(uint8_t i=0; i<=32; i++){
					drawEditModeMessage(&spiData, i);
				}
				for(uint8_t i=32; i>0; i--){
					drawEditClockModeNumbers(&spiData, &rtc, &editNumbers, &editMode, i);
				}
				editSwitchTimeout = 0;
				editMode = !editMode;
			}

		} else{
			if (editSwitchTimeout != 0){
				editSwitchTimeout = 0;
			}
		}

		if(isCurrentTick(&previousTimeDot, 1000)){
			isDot = !isDot;
			previousTimeDot = getRunningTime();
		}
		
		if(isCurrentTick(&previousTimeSecound, 10) && !dateMode){
			if(!editMode){
				drawClockModeNumbers(&spiData, &rtc, isDot, 0, (!isInvert)? editSwitchTimeout/(editSwitchDuration/255) : isInvert);
			} else {
				drawEditClockModeNumbers(&spiData, &rtc, &editNumbers, &editMode, 0);
			}
			previousTimeSecound = getRunningTime();
		}

		if(dateMode){
			drawDateModeNumbers(&spiData, &rtc, isDot, 0, isInvert);
			if(isCurrentTick(&previousDateSecound, 10000)){
				dateMode = !dateMode;
			}
		}

		if(isButtonPressed(BTN2_PIN) && !editMode){
			dateMode = !dateMode;
			if(dateMode){
				for(uint8_t i=0; i<=32; i++){
					drawClockModeNumbers(&spiData, &rtc, isDot, i, isInvert);
				}
				for(uint8_t i=32; i>0; i--){
					drawDateModeNumbers(&spiData, &rtc, isDot, i, isInvert);
				}
			} else{
				for(uint8_t i=0; i<=32; i++){
					drawDateModeNumbers(&spiData, &rtc, isDot, i, isInvert);
				}
				for(uint8_t i=32; i>0; i--){
					drawClockModeNumbers(&spiData, &rtc, isDot, i, isInvert);
				}
			}

			previousDateSecound = getRunningTime();
		}

		if(isCurrentTick(&previousInvertSecound, (!isInvert)?900000 : 7500)){
			isInvert = (!isInvert)? 255 : 0;
			previousInvertSecound = getRunningTime();
		}
	}
}
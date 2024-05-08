#include "moduleInitialization.h"


void initRTCModule(ds3231_rtc_t* rtc){
    ds3231_init(DS3231_I2C_PORT, DS3231_SDA, DS3231_SCL, rtc);
}

void initSpiData(SH1122_SPI* oledSPI){
	oledSPI->width = WIDTH;
	oledSPI->height = HEIGHT;
	oledSPI->rate = SPI_RATE;
	oledSPI->spi = SPI_PORT;
	
	oledSPI->pin_sclk = SCLK;
	oledSPI->pin_mosi = MOSI;
	oledSPI->pin_res = RES;
	oledSPI->pin_dc = DC;
	oledSPI->pin_cs = CS;
	
	sh1122_init_pins(oledSPI);
	sh1122_init_data(oledSPI);
}

void initButton(uint pin){
	gpio_init(pin);
    gpio_set_dir(pin, GPIO_IN);
    gpio_pull_up(pin);
}

void initMainModules(ds3231_rtc_t* rtc, SH1122_SPI* oledSPI){
	initRTCModule(rtc);
	initSpiData(oledSPI);
}
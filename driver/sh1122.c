#include "sh1122.h"

const uint8_t SET_COL_ADR_LSB =  0x0;
const uint8_t SET_COL_ADR_MSB = 0x10;
const uint8_t SET_DISP_START_LINE = 0x40;
const uint8_t SET_CONTRAST =0x81;
const uint8_t SET_SEG_REMAP = 0xA0;
const uint8_t SET_ENTIRE_ON = 0xA4;
const uint8_t SET_NORM_INV = 0xA6;
const uint8_t SET_MUX_RATIO = 0xA8;
const uint8_t SET_CTRL_DCDC = 0xAD;
const uint8_t SET_DISP = 0xAE;
const uint8_t SET_ROW_ADR = 0xB0;
const uint8_t SET_COM_OUT_DIR = 0xC0;
const uint8_t SET_DISP_OFFSET = 0xD3;
const uint8_t SET_DISP_CLK_DIV = 0xD5;
const uint8_t SET_PRECHARGE = 0xD9;
const uint8_t SET_VCOM_DESEL = 0xDB;
const uint8_t SET_VSEG_LEVEL = 0xDC;
const uint8_t SET_DISCHARGE_LEVEL = 0x30;

void sh1122_init_pins(SH1122_SPI* spiData){
	spi_init(spiData->spi, spiData->rate);

	gpio_set_function(spiData->pin_mosi, GPIO_FUNC_SPI);
	gpio_set_function(spiData->pin_sclk, GPIO_FUNC_SPI);

	gpio_init(spiData->pin_cs);
	gpio_init(spiData->pin_res);
	gpio_init(spiData->pin_dc);

	gpio_set_dir(spiData->pin_cs, GPIO_OUT);
	gpio_set_dir(spiData->pin_res, GPIO_OUT);
	gpio_set_dir(spiData->pin_dc, GPIO_OUT);

	gpio_put(spiData->pin_dc, 0);
	gpio_put(spiData->pin_cs, 1);



	gpio_put(spiData->pin_res, 1);
	sleep_ms(1);
	gpio_put(spiData->pin_res, 0);
	sleep_ms(10);
	gpio_put(spiData->pin_res, 1);
}

void sh1122_init_data(SH1122_SPI* spiData){
	uint8_t displayCommands[] = {
        SET_DISP | 0x00,  // off
        // address setting
        SET_COL_ADR_LSB,
        SET_COL_ADR_MSB,  // horizontal
        // resolution and layout
        SET_DISP_START_LINE | 0x00,
        SET_SEG_REMAP,
        SET_MUX_RATIO,
        spiData->height - 1,
        SET_COM_OUT_DIR,  // scan from COM0 to COM[N]
        SET_DISP_OFFSET,
        0x00,
        // display
        SET_CONTRAST,
        0x80,  // median
        SET_ENTIRE_ON,  // output follows RAM contents
        SET_NORM_INV,  // not inverted
        SET_DISP | 0x01,
	};
	
	for(int i=0; i<sizeof(displayCommands)/sizeof(uint8_t); i++){
		sh1122_write_cmd(spiData, displayCommands[i]);
	}

}


void sh1122_write_cmd(SH1122_SPI* spiData, uint8_t cmd){
	gpio_put(spiData->pin_cs, 1);
	gpio_put(spiData->pin_dc, 0);
	gpio_put(spiData->pin_cs, 0);
	spi_write_blocking(spiData->spi, &cmd, 1);
	gpio_put(spiData->pin_cs, 1);
}

void sh1122_write_data(SH1122_SPI* spiData, uint8_t* buffer, size_t len){
	gpio_put(spiData->pin_cs, 1);
	gpio_put(spiData->pin_dc, 1);
	gpio_put(spiData->pin_cs, 0);
	spi_write_blocking(spiData->spi, buffer, len);
	gpio_put(spiData->pin_cs, 1);
}

void sh1122_show(SH1122_SPI* spiData, uint8_t* buffer, size_t len){
	sh1122_write_cmd(spiData, SET_COL_ADR_LSB);
	sh1122_write_cmd(spiData, SET_COL_ADR_MSB);
	sh1122_write_cmd(spiData, SET_ROW_ADR);

	sh1122_write_data(spiData, buffer, len);
}

void sh1122_poweroff(SH1122_SPI* spiData){
	sh1122_write_cmd(spiData, (SET_DISP | 0x00));
}

void sh1122_poweron(SH1122_SPI* spiData){
	sh1122_write_cmd(spiData, (SET_DISP | 0x01));
}

void sh1122_contrast(SH1122_SPI* spiData, uint8_t contrast){
	sh1122_write_cmd(spiData, SET_CONTRAST);
	sh1122_write_cmd(spiData, contrast);
}

void sh1122_flip(SH1122_SPI* spiData){
	sh1122_write_cmd(spiData, SET_DISP_START_LINE | 0x20);
	sh1122_write_cmd(spiData, 0XA1);
	sh1122_write_cmd(spiData, 0XC8);
}

void sh1122_invert(SH1122_SPI* spiData, uint8_t invert){
	sh1122_write_cmd(spiData, (SET_NORM_INV | (invert & 1)));
}
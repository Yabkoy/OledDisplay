#include "sh1122.h"

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


void sh1122_Init_Data(SH1122_SPI* spiData){
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

	sh1122_write_cmd(spiData, SET_COL_ADR_LSB);
	sh1122_write_cmd(spiData, SET_COL_ADR_MSB);
	sh1122_write_cmd(spiData, SET_ROW_ADR);

	sh1122_write_data(spiData, testBuffer, sizeof(testBuffer)/sizeof(uint8_t));
}


void sh1122_Init_Pins(SH1122_SPI* spiData){
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

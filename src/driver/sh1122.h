///This library was based on micropython code that handle sh1122 communication via SPI.
///I rewrite it to C library, using raspberry pi pico c/c++ sdk
///
///Orginal code: https://github.com/fdufnews/pico_examples
///drivers/sh1122.py is file that i used
///


#ifndef SH1122_H
#define SH1122_H

#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/spi.h"
#include "hardware/gpio.h"

extern const uint8_t SET_COL_ADR_LSB;
extern const uint8_t SET_COL_ADR_MSB;
extern const uint8_t SET_DISP_START_LINE;
extern const uint8_t SET_CONTRAST;
extern const uint8_t SET_SEG_REMAP;
extern const uint8_t SET_ENTIRE_ON;
extern const uint8_t SET_NORM_INV;
extern const uint8_t SET_MUX_RATIO;
extern const uint8_t SET_CTRL_DCDC;
extern const uint8_t SET_DISP;
extern const uint8_t SET_ROW_ADR;
extern const uint8_t SET_COM_OUT_DIR;
extern const uint8_t SET_DISP_OFFSET;
extern const uint8_t SET_DISP_CLK_DIV;
extern const uint8_t SET_PRECHARGE;
extern const uint8_t SET_VCOM_DESEL;
extern const uint8_t SET_VSEG_LEVEL;
extern const uint8_t SET_DISCHARGE_LEVEL;

typedef struct {
    int width;
    int height;
    int rate;
    
    spi_inst_t* spi;

    uint pin_sclk;
    uint pin_mosi;
    uint pin_dc;
    uint pin_res;
    uint pin_cs;
} SH1122_SPI;

void sh1122_init_pins(SH1122_SPI* spiData);
void sh1122_init_data(SH1122_SPI* spiData);

void sh1122_write_cmd(SH1122_SPI* spiData, uint8_t cmd);
void sh1122_write_data(SH1122_SPI* spiData, uint8_t* buffer, size_t len);

void sh1122_show(SH1122_SPI* spiData, uint8_t* buffer, size_t len);
void sh1122_poweroff(SH1122_SPI* spiData);
void sh1122_poweron(SH1122_SPI* spiData);
void sh1122_contrast(SH1122_SPI* spiData, uint8_t contrast);
void sh1122_flip(SH1122_SPI* spiData);
void sh1122_invert(SH1122_SPI* spiData, uint8_t invert);

#endif // SH1122_H

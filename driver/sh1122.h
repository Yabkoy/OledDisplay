#ifndef SH1122_H
#define SH1122_H

#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/spi.h"
#include "hardware/gpio.h"

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

uint8_t testBuffer[] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};

typedef struct {
    int width;
    int height;
    int pages;
    int rate;
    
    spi_inst_t* spi;

    uint pin_sclk;
    uint pin_mosi;
    uint pin_dc;
    uint pin_res;
    uint pin_cs;
} SH1122_SPI;

void sh1122_write_cmd(SH1122_SPI* spiData, uint8_t cmd);
void sh1122_write_data(SH1122_SPI* spiData, uint8_t* buffer, size_t len);
void sh1122_Init_Data(SH1122_SPI* spiData);
void sh1122_Init_Pins(SH1122_SPI* spiData);

#endif // SH1122_H
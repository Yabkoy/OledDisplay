#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/spi.h"
#include "hardware/gpio.h"

uint8_t SET_COL_ADR_LSB =  0x0;
uint8_t SET_COL_ADR_MSB = 0x10;
uint8_t SET_DISP_START_LINE = 0x40;
uint8_t SET_CONTRAST =0x81;
uint8_t SET_SEG_REMAP = 0xA0;
uint8_t SET_ENTIRE_ON = 0xA4;
uint8_t SET_NORM_INV = 0xA6;
uint8_t SET_MUX_RATIO = 0xA8;
uint8_t SET_CTRL_DCDC = 0xAD;
uint8_t SET_DISP = 0xAE;
uint8_t SET_ROW_ADR = 0xB0;
uint8_t SET_COM_OUT_DIR = 0xC0;
uint8_t SET_DISP_OFFSET = 0xD3;
uint8_t SET_DISP_CLK_DIV = 0xD5;
uint8_t SET_PRECHARGE = 0xD9;
uint8_t SET_VCOM_DESEL = 0xDB;
uint8_t SET_VSEG_LEVEL = 0xDC;
uint8_t SET_DISCHARGE_LEVEL = 0x30;

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

#ifndef SCALING_H
#define SCALING_H
#include "pico/stdlib.h"
#include <stdlib.h>

uint8_t nearestNeighboruint8_terpolation(const uint8_t* buffer, uint8_t width, uint8_t x, uint8_t y);
uint8_t* scaleImageNearestNeighbor(const uint8_t* buffer, uint8_t width, uint8_t height, uint8_t scale);

#endif
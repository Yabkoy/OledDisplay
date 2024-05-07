#ifndef DISPLAYBUFFER_H
#define DISPLAYBUFFER_H
#include "pico/stdlib.h"
#include <stdlib.h>
#include <string.h>

typedef struct 
{
    size_t width;
    size_t height;
    size_t bufferLen;
    uint8_t* buffer;
} displayBuffer;

void initDisplayBuffer(displayBuffer* buffer, size_t width, size_t height);
void fillBufferWithValue(displayBuffer* buffer, uint8_t value);
void addBufferToDisplay(displayBuffer* dBuffer, const uint8_t* number, uint8_t w, uint8_t h, uint8_t x, uint8_t y);

uint8_t convertPixelsToOledPixel(uint8_t p1, uint8_t p2);
void convertNormalDisplayBufferToOledBuffer(displayBuffer* buffer);

void deAllocBuffer(displayBuffer* buffer);

#endif
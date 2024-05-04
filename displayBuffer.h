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

#endif
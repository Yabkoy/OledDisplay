#include "displayBuffer.h"

void initDisplayBuffer(displayBuffer* dBuffer, size_t width, size_t height){
    dBuffer->bufferLen = (width*height)*sizeof(uint8_t);
    dBuffer->buffer = (uint8_t*)malloc(dBuffer->bufferLen);
    memset(dBuffer->buffer, 0, dBuffer->bufferLen);
}

void fillBufferWithValue(displayBuffer* buffer, uint8_t value){
    memset(buffer->buffer, value, buffer->bufferLen);
}


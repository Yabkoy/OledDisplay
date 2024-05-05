#include "displayBuffer.h"

uint8_t convertPixelsToOledPixel(uint8_t p1, uint8_t p2){
    return (p1 << 4) | p2;
}


void initDisplayBuffer(displayBuffer* dBuffer, size_t width, size_t height){
    dBuffer->bufferLen = (width*height)*sizeof(uint8_t);
    dBuffer->buffer = (uint8_t*)malloc(dBuffer->bufferLen);
    memset(dBuffer->buffer, 0, dBuffer->bufferLen);
}

void fillBufferWithValue(displayBuffer* buffer, uint8_t value){
    memset(buffer->buffer, value, buffer->bufferLen);
}


void convertNormalDisplayBufferToOledBuffer(displayBuffer* buffer){
    size_t newBufferSize = (buffer->bufferLen)/2;
    uint8_t* newDisplayBufferData = (uint8_t*)malloc(newBufferSize);
    
    for(int i=0; i<newBufferSize; i++){    
        uint8_t d1 = (buffer->buffer[i*2]) / 16; 
        uint8_t d2 = (buffer->buffer[(i*2)+1]) / 16; 
        newDisplayBufferData[i] = convertPixelsToOledPixel(d1, d2);
    }

    free(buffer->buffer);

    buffer->buffer = newDisplayBufferData;
    buffer->bufferLen = newBufferSize;
}

void deAllocBuffer(displayBuffer* buffer){
    free(buffer->buffer);
}
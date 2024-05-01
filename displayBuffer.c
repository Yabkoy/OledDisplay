#include "displayBuffer.h"

displayBuffer initDisplayBuffer(size_t width, size_t height){
    displayBuffer dBuffer;
    dBuffer.bufferLen = (width*height)*sizeof(uint8_t);
    dBuffer.buffer = (uint8_t*)malloc(dBuffer.bufferLen);
    
    return dBuffer;
}

void fillBufferWithValue(displayBuffer* buffer, uint8_t value){
    size_t* bufferLen = &buffer->bufferLen;

    for(int i=0; i<*buffferLen; i++){
        buffer->buffer[i] = value;
    }
}


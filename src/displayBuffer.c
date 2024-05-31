#include "displayBuffer.h"

void initDisplayBuffer(displayBuffer* dBuffer, size_t width, size_t height){
    dBuffer->width = width;
    dBuffer->height = height;

    dBuffer->bufferLen = (width*height)*sizeof(uint8_t);
    dBuffer->buffer = (uint8_t*)malloc(dBuffer->bufferLen);
    memset(dBuffer->buffer, 0, dBuffer->bufferLen);
}

void fillBufferWithValue(displayBuffer* buffer, uint8_t value){
    memset(buffer->buffer, value, buffer->bufferLen);
}

void changeBrightness(displayBuffer* buffer, uint8_t intensity){
    for(int i=0; i<buffer->bufferLen; i++){
        if(buffer->buffer[i] != 0){
            buffer->buffer[i] += intensity;
        }
    }
}

void addDisplayBufferToDisplayBuffer(displayBuffer* sourceBuffer, displayBuffer* inputBuffer, uint8_t x, uint8_t y){
    addUint8TBufferToDisplay(sourceBuffer, inputBuffer->buffer, inputBuffer->width, inputBuffer->height, x, y);
}

void addUint8TBufferToDisplay(displayBuffer* sourceBuffer, const uint8_t* inputBuffer, uint16_t w, uint16_t h, uint8_t x, uint8_t y){
	for(int i=0; i<h; i++){
		for(int j=0; j<w; j++){
            size_t sourceBufferElement = (((i+y)*256)+j)+x;
            size_t inputBufferElement = ((i*w)+j);
            if(sourceBufferElement >= sourceBuffer->bufferLen){
                continue;
            }
			sourceBuffer->buffer[sourceBufferElement] = inputBuffer[inputBufferElement];
		}
	}
}
void dimBufferFromTopAndBottom(displayBuffer* sourceBuffer, size_t level){
    for(int i=0; i<level; i++){
        for(int j=0; j<sourceBuffer->width; j++){
            size_t bufElement1 = (i*sourceBuffer->width)+j;
            size_t bufElement2 = (sourceBuffer->bufferLen-1)-((i*sourceBuffer->width)+j);

            sourceBuffer->buffer[bufElement1] = 0;
            sourceBuffer->buffer[bufElement2] = 0;
        }
    }
}

uint8_t convertPixelsToOledPixel(uint8_t p1, uint8_t p2){
    return (p1 << 4) | p2;
}

void convertNormalDisplayBufferToOledBuffer(displayBuffer* buffer){
    size_t newBufferSize = (buffer->bufferLen)/2;
    uint8_t* newDisplayBufferData = (uint8_t*)malloc(newBufferSize);
    
    for(int i=0; i<newBufferSize; i++){    
        uint8_t d1 = (buffer->buffer[i*2]) / 16; 
        uint8_t d2 = (buffer->buffer[(i*2)+1]) / 16; 
        uint8_t dataResult = convertPixelsToOledPixel(d1, d2);
        
        newDisplayBufferData[i] = dataResult;
    }

    free(buffer->buffer);

    buffer->buffer = newDisplayBufferData;
    buffer->bufferLen = newBufferSize;
}

void deAllocBuffer(displayBuffer* buffer){
    free(buffer->buffer);
}
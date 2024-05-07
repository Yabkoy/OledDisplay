#include "scaling.h"

uint8_t nearestNeighboruint8_terpolation(const uint8_t* buffer, uint8_t width, uint8_t x, uint8_t y) {
    return buffer[y * width + x];
}


uint8_t* scaleImageNearestNeighbor(const uint8_t* buffer, uint8_t width, uint8_t height, uint8_t scale) {
    uint8_t newWidth = width*scale;
    uint8_t newHeight = height*scale;
    
    uint8_t* scaledBuffer = (uint8_t*)malloc((newWidth * newHeight)*sizeof(uint8_t));

    float xRatio = (float)width / newWidth;
    float yRatio = (float)height / newHeight;

    for (uint8_t i = 0; i < newHeight; ++i) {
        for (uint8_t j = 0; j < newWidth; ++j) {
            float originalX = j * xRatio;
            float originalY = i * yRatio;

            scaledBuffer[i * newWidth + j] = nearestNeighboruint8_terpolation(buffer, width, originalX, originalY);
        }
    }

    return scaledBuffer;
}
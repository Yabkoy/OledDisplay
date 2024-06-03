///Helpful script for converting cpp2img result to uint8_t, that is used in this project
#include <stdio.h>

const uint16_t bitmapData[] = {};

uint8_t convertToUint8(uint16_t value) {

    return (uint8_t)(value & 0xFF);
}

void printUint8Hex(uint8_t value) {
    printf("0x%02X, ", value);
}

void printBitmapInUint8_t(const uint16_t* bitmap, size_t bitmapSize){
    for(int i=0; i<bitmapSize; i++){
        uint8_t con = convertToUint8(bitmap[i]);
        printUint8Hex(con);
        if((i+1)%16 == 0){
            printf("\n");
        }
    }
}

int main()
{
    printBitmapInUint8_t(bitmapData, sizeof(bitmapData)/sizeof(uint16_t));
}
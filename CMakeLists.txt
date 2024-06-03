cmake_minimum_required(VERSION 3.13)

# initialize the SDK based on PICO_SDK_PATH
# note: this must happen before project()
include(pico_sdk_import.cmake)

set(CMAKE_BUILD_TYPE "Debug") 

# Setting for buttons data
set(BTN1_PIN 17 CACHE STRING "Pin number for button 1 (edit button)")
set(BTN2_PIN 16 CACHE STRING "Pin number for button 2 (change value button)")
#
## SPI SH1122 Oled display data
set(WIDTH 256 CACHE STRING "Width of oled display")
set(HEIGHT 64 CACHE STRING "Height of oled display")

## Pico SPI data setting
set(SPI_PORT spi0 CACHE STRING "SPI number on which oled display is working")
set(SPI_RATE 10485760 CACHE STRING "SPI protocol hz Frequency")

set(SCLK 18 CACHE STRING "SCLK pin for spi protocol")
set(MOSI 19 CACHE STRING "MOSI pin for spi protocol")
set(RES 3 CACHE STRING "RES pin for spi protocol")
set(DC 4 CACHE STRING "DC pin for spi protocol")
set(CS 5 CACHE STRING "CS pin for spi protocol")
#
#
## i2c DS3231 module setting
set(DS3231_I2C_PORT i2c0 CACHE STRING "i2c number on which module is working")
set(DS3231_SDA 20 CACHE STRING "SDA pin for i2c protocol. On my board its D")
set(DS3231_SCL 21 CACHE STRING "SCL pin for i2c protocol. On my board its C")
#
#
## Setting preprocessor data for compile process
add_compile_definitions(BTN1_PIN=${BTN1_PIN})
add_compile_definitions(BTN2_PIN=${BTN2_PIN})
#
add_compile_definitions(WIDTH=${WIDTH})
add_compile_definitions(HEIGHT=${HEIGHT})
#
add_compile_definitions(SPI_PORT=${SPI_PORT})
add_compile_definitions(SPI_RATE=${SPI_RATE})
#
add_compile_definitions(SCLK=${SCLK})
add_compile_definitions(MOSI=${MOSI})
add_compile_definitions(RES=${RES})
add_compile_definitions(DC=${DC})
add_compile_definitions(CS=${CS})
#

#
add_compile_definitions(DS3231_I2C_PORT=${DS3231_I2C_PORT})
add_compile_definitions(DS3231_SDA=${DS3231_SDA})
add_compile_definitions(DS3231_SCL=${DS3231_SCL})

project(OledDisplay)

# initialize the Raspberry Pi Pico SDK
pico_sdk_init()

# rest of your project
add_executable(${PROJECT_NAME}
	src/main.c
	src/bitmapsData.c
	src/scaling.c
	src/moduleInitialization.c
	src/programLoop.c
	src/dateAndTimeValidation.c
	src/editTimeDrawingValidation.c
	src/numberDrawing.c
	src/displayBuffer.c
	src/driver/sh1122.c
	src/driver/ds3231.c
)

option(INTRO_ANIMATION "Enables INTRO ANIMATION ON STARTUP" ON)

if(INTRO_ANIMATION)
    add_compile_definitions(INTRO_ANIMATION)
endif()


# Add pico_stdlib library which aggregates commonly used features
target_link_libraries(${PROJECT_NAME} pico_stdlib hardware_spi hardware_i2c hardware_gpio)

# create map/bin/hex/uf2 file in addition to ELF.
pico_add_extra_outputs(${PROJECT_NAME})

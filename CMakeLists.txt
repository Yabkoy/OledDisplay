cmake_minimum_required(VERSION 3.13)

# initialize the SDK based on PICO_SDK_PATH
# note: this must happen before project()
include(pico_sdk_import.cmake)

set(CMAKE_BUILD_TYPE "Debug") 

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

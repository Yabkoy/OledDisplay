cmake_minimum_required(VERSION 3.12)

project(sh1122)

add_library(sh1122
    sh1122.c
    sh1122.h
)

target_link_libraries(${PROJECT_NAME} pico_stdlib hardware_spi)
pico_add_extra_outputs(sh1122)

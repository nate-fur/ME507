cmake_minimum_required(VERSION 3.12)
project(ME507 CXX)

set(CMAKE_CXX_STANDARD 11)
set(MCU __AVR_ATmega64__)

include_directories(
        include
        include/ridgely_inc
        include/Adafruit_BNO055
        ../untitled/avr/cores
        ../untitled/avr/libraries/Wire
        ridgley_code)

set(SOURCE_FILES src/main.cpp)

add_executable(main src/main.cpp src/ATMega/Adafruit_BNO055.cpp)


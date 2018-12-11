cmake_minimum_required(VERSION 3.7)
project(ME507 CXX)

set(CMAKE_CXX_STANDARD 11)
set(MCU __AVR_ATmega64__)

include_directories(
        borrowed_code
        borrowed_code/ridgely_code
        borrowed_code/Adafruit_BNO055
        ../untitled/avr/cores
        ../untitled/avr/libraries/Wire
        ridgley_code)

set(SOURCE_FILES my_src/main_mega.cpp)

add_executable(main my_src/main_mega.cpp borrowed_code/Adafruit_BNO055/Adafruit_BNO055.cpp)


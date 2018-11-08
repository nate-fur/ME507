cmake_minimum_required(VERSION 3.12)
project(ME507 CXX)

set(CMAKE_CXX_STANDARD 11)

include_directories(include include/Adafruit_BNO055 ../untitled/avr/cores ../untitled/avr/libraries/Wire)


add_executable(main src/ATMega/Adafruit_BNO055.cpp ridgely_code/lab1/adc.cpp)


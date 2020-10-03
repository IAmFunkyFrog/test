cmake_minimum_required(VERSION 3.17)
project(home_0210 C ASM)

set(CMAKE_C_STANDARD 99)

add_definitions(-O2)
add_executable(home_0210 main.c sort.h sort.s)
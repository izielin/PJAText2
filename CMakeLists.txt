cmake_minimum_required(VERSION 3.17)
project(PJAText2)

set(CMAKE_CXX_STANDARD 17)

set(SOURCE_FILES main.cpp counters.cpp counters.h global.h)
add_executable(PJAText2 ${SOURCE_FILES})

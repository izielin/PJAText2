cmake_minimum_required(VERSION 3.17)
project(PJAText2)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-pedantic")

set(SOURCE_FILES
        global.h
        main.cpp
        counters/counters.cpp
        collectors/palindromes_collector.cpp
        collectors/passed_words_collector.cpp
        collectors/anagrams_collector.cpp
        utils/check_arguments_correctness.cpp
        utils/utility_functions.cpp
        utils/invoke_functions.cpp custom_containers/container.cpp)
add_executable(PJAText2 ${SOURCE_FILES})

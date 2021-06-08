cmake_minimum_required(VERSION 3.17)
project(PJAText2)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-pedantic")

set(SOURCE_FILES
        main.cpp
        src/wrappers/arguments_wrapper.cpp
        src/wrappers/input_data_wrapper.cpp
        tools/src/collectors/palindromes_collector.cpp
        tools/src/collectors/words_collector.cpp
        tools/src/collectors/anagrams_collector.cpp
        tools/src/collectors/path_collector.cpp
        src/utils/check_arguments_correctness.cpp
        src/utils/utility_functions.cpp
        src/utils/run_function.cpp
        tools/src/counters/number_counter.cpp
        tools/src/counters/digit_counter.cpp
        tools/src/counters/char_counter.cpp global/global_variables.h global/global_aliases.h)
add_executable(PJAText2 ${SOURCE_FILES})

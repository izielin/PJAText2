//
// Created by mmich on 30.05.2021.
//

#ifndef PJATEXT2_UTILITY_FUNCTIONS_H
#define PJATEXT2_UTILITY_FUNCTIONS_H

#include <iostream>
#include <set>
#include "stream_helper.h"


namespace utility {
    template<template<typename, typename...> class TT, typename Args>
    void print_container(const TT<Args> &container, stream_helper &output_stream);

    void ltrim(std::string &s);

    void rtrim(std::string &s);

    void trim(std::string &s);

    std::ifstream open_file(const std::string &path_to_file);

    void load_file_by_words(const std::string &path_to_file);

    void count_lines_in_file(std::string &path_to_file, stream_helper &output_stream);

    void load_file_by_line(std::vector<std::string> &vector, const std::string &path);
}

#include "utility_functions.tpp"

#endif //PJATEXT2_UTILITY_FUNCTIONS_H

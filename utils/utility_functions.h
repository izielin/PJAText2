#ifndef PJATEXT2_UTILITY_FUNCTIONS_H
#define PJATEXT2_UTILITY_FUNCTIONS_H

#include <iostream>
#include <set>
#include "stream_helper.h"
#include "../wrappers/input_data_wrapper.h"


namespace utility {
    template<template<typename, typename...> class TT, typename Args>
    void print_container(const TT<Args> &container, stream_helper &output_stream);

    std::string trim(std::string &s);

    std::ifstream open_file_to_read(const std::string &path_to_file);

    std::ofstream open_file_to_write(const std::string &path_to_file);

    void load_file_by_words(wrappers::input_data_wrapper &container, const std::string &path_to_file);

    void count_lines_in_file(std::string &path_to_file, stream_helper &output_stream);

    void load_file_by_line(std::vector<std::string> &vector, const std::string &path);

    void merge_files(std::vector<std::string> &to_merge_path, std::string &base_path);
}

#include "utility_functions.tpp"

#endif

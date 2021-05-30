//
// Created by mmich on 30.05.2021.
//

#ifndef PJATEXT2_UTILITY_FUNCTIONS_H
#define PJATEXT2_UTILITY_FUNCTIONS_H

#include <iostream>
#include <set>


namespace utility {
    template<template<typename, typename...> class TT, typename Args>
    void print_container(const TT<Args> &container) {
        for (auto it = container.begin(); it != container.end(); ++it) {
            if (it != container.begin())
                std::cout << ", ";
            std::cout << *it;
        }
        std::cout << '\n';
    }

    void ltrim(std::string &s);

    void rtrim(std::string &s);

    void trim(std::string &s);

    std::ifstream open_file(const std::string &path_to_file);

    void load_file(const std::string &path_to_file);

    void count_lines_in_file(std::string &path_to_file);
}


#endif //PJATEXT2_UTILITY_FUNCTIONS_H

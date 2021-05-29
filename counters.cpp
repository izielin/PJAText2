//
// Created by mmich on 28.05.2021.
//

#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <fstream>


#include "counters.h"
#include "global.h"

/**
* @brief check_is_double - check given string is double
* @param input_string - string for checking
* @return true if string is double, false if not
*/
bool check_is_double(const std::string &input_string) {
    char *end_pointer = 0;
    strtod(input_string.c_str(), &end_pointer);

    if (*end_pointer != '\0' || end_pointer == input_string.c_str())
        return false;
    return true;
}

void counting_methods::number_counter::count() {
    // TODO: not cover negative number
    amount = std::count_if(input_vector.begin(), input_vector.end(), check_is_double);
}

int counting_methods::number_counter::get_amount() const {
    return amount;
}

void counting_methods::digit_counter::count() {
    // TODO: not cover negative number
    std::for_each(input_vector.begin(), input_vector.end(), [&](auto &&s) {
        amount += std::count_if(s.begin(), s.end(), [](char &c) { return std::isdigit(c); });
    });
}

int counting_methods::digit_counter::get_amount() const {
    return amount;
}

int counting_methods::char_counter::get_amount() const {
    return amount;
}

void counting_methods::char_counter::count(const std::string &path) {
    std::ifstream in(path);

    for (auto line = std::string(); std::getline(in, line);) {
        amount += line.size();
    }

    in.close();
}

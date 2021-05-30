//
// Created by mmich on 28.05.2021.
//

#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <fstream>


#include "counters.h"
#include "../global.h"

/**
* @brief check_is_double - check given string is double
* @param input_string - string for checking
* @return true if string is double, false if not
*/
bool check_is_double(const std::string &input_string) {
    char *endptr; //address of the character at which conversion has finished
    strtod(input_string.c_str(), &endptr);
    return input_string.c_str() != endptr;
}

void counters::number_counter::count() {
    amount = std::count_if(input_vector.begin(), input_vector.end(), check_is_double);
}

int counters::number_counter::get_amount() const {
    return amount;
}

void counters::digit_counter::count() {
    std::for_each(input_vector.begin(), input_vector.end(), [&](auto &&s) {
        amount += std::count_if(s.begin(), s.end(), [](char &c) { return std::isdigit(c); });
    });
}

int counters::digit_counter::get_amount() const {
    return amount;
}

int counters::char_counter::get_amount() const {
    return amount;
}

void counters::char_counter::count(const std::string &path) {
    std::ifstream in(path);

    for (auto line = std::string(); std::getline(in, line);) {
        amount += line.size();
    }

    in.close();
}

//
// Created by mmich on 28.05.2021.
//

#include <iostream>
#include <algorithm>
#include <cstdlib>


#include "counters.h"
#include "global.h"

/**
* @brief checkIsDouble - check inputString is double and if true return double result
* @param inputString - string for checking
* @param result - return double value
* @return true if string is double, false if not
*/
bool checkIsDouble(const std::string &s) {
    char *endptr = 0;
    strtod(s.c_str(), &endptr);

    if (*endptr != '\0' || endptr == s.c_str())
        return false;
    return true;
}


void counting_methods::number_counter::count() {
    amount = std::count_if(input_vector.begin(), input_vector.end(), checkIsDouble);
}

int counting_methods::number_counter::get_amount() const {
    return amount;
}

void counting_methods::digit_counter::count() {
    std::for_each(input_vector.begin(), input_vector.end(), [&](auto &&s) {
        amount += std::count_if(s.begin(), s.end(), [](char &c) { return std::isdigit(c); });
    });
}

int counting_methods::digit_counter::get_amount() const {
    return amount;
}

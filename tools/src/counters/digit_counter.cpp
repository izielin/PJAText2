#include <iostream>
#include <algorithm>

#include "../../include/counters/digit_counter.h"

counters::digit_counter::digit_counter() = default;

counters::digit_counter::~digit_counter() = default;

int counters::digit_counter::amount() const {
    return _amount;
}

/**
 * Count digits in the given vector.
 * @param vector_searched - vector in which to count the characters
 */
void counters::digit_counter::count(std::vector<std::string> &vector_searched) {
    std::for_each(vector_searched.begin(), vector_searched.end(), [&](auto &s) {
        _amount += std::count_if(s.begin(), s.end(), [](char &c) { return std::isdigit(c); });
    });
}

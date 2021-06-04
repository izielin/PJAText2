#include <iostream>

#include "../../include/counters/char_counter.h"
#include "../../../include/utils/utility_functions.h"

counters::char_counter::char_counter() = default;

counters::char_counter::~char_counter() = default;

int counters::char_counter::amount() const {
    return _amount;
}

/**
 * Count characters in the given vector.
 * @param vector_searched - vector in which to count the characters
 */
void counters::char_counter::count(std::vector<std::string> &vector_searched) {
    std::for_each(vector_searched.begin(), vector_searched.end(), [&](const std::string &elem) {
        _amount += elem.length();
    });
}
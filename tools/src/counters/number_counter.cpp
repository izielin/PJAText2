#include <iostream>
#include <regex>

#include "../../include/counters/number_counter.h"

counters::number_counter::number_counter() = default;

counters::number_counter::~number_counter() = default;

int counters::number_counter::amount() const {
    return _amount;
}

/**
 * Check if given string is real number.
 * @param input_string - string to chceck
 * @return true if string is real number, false if no
 */
bool check_is_double(const std::string &input_string) {
    std::regex num_regex(R"(^[-]?[0-9]+\.?[0-9]*|\.?[0-9]+|[0-9]*[eE][+-][0-9]+\.?[0-9]*$)");
    return (std::regex_match(input_string, num_regex));
}

/**
 * Count numbers in the given vector.
 * @param vector_searched - vector in which to count the characters
 */
void counters::number_counter::count(std::vector<std::string> &vector_searched) {
    _amount = std::count_if(vector_searched.begin(), vector_searched.end(), check_is_double);
}
#include <iostream>
#include <algorithm>
#include <fstream>
#include <regex>

#include "counters.h"


bool check_is_double(const std::string &input_string) {
    // R -> raw string literal - no need to escape characters like (\, " \n)
    std::regex num_regex(R"(^[-]?([0-9]+\.?[0-9]*|\.?[0-9]+)|[0-9]|[0-9]+[eE][+-][0-9]+\.?[0-9]*$)");
    return (std::regex_match(input_string, num_regex));
}

void counters::number_counter::count(std::vector<std::string> &input) {
    amount = std::count_if(input.begin(), input.end(), check_is_double);
}

int counters::number_counter::get_amount() const {
    return amount;
}

void counters::digit_counter::count(std::vector<std::string> &input) {
    std::for_each(input.begin(), input.end(), [&](auto &&s) {
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

//
// Created by mmich on 01.06.2021.
//

#include <iostream>

#include "enhanced_vector.h"
#include "../utils/utility_functions.h"
#include "../counters/counters.h"
#include "../collectors/anagrams_collector.h"
#include "../collectors/palindromes_collector.h"


void containers::enhanced_vector::print_digits_amount() {
    auto counter = counters::digit_counter();
    counter.count(data_vector);
    output_stream << counter.get_amount() << '\n';
}

void containers::enhanced_vector::print_numbers_amount() {
    auto counter = counters::number_counter();
    counter.count(data_vector);
    output_stream << counter.get_amount() << '\n';
}

void containers::enhanced_vector::print_chars_amount(containers::argument_container &container, int position) {
    auto it = container.reverse_find_path(position); // search last loaded file path before flag
    if (it != container.getArguments().rend()) {
        auto counter = counters::char_counter();
        counter.count(*it);
        output_stream << counter.get_amount() << '\n';
    }
}

void containers::enhanced_vector::print_word_amount() {
    output_stream << data_vector.size() << '\n';
}

void containers::enhanced_vector::sort_alphabetically(containers::argument_container &container, int position) {
    if (container[position - 1] == "-l")
        enhanced_vector::sort([](std::string &a, std::string &b) { return a.length() < b.length(); });
    else
        enhanced_vector::sort([](std::string &a, std::string &b) { return a < b; });
}

void containers::enhanced_vector::sort_reverse_alphabetically(containers::argument_container &container, int position) {
    if (container[position - 1] == "-l")
        enhanced_vector::sort([](std::string &a, std::string &b) { return b.length() < a.length(); });
    else
        enhanced_vector::sort([](std::string &a, std::string &b) { return b < a; });
}

void containers::enhanced_vector::print_anagrams(containers::argument_container &container, int position) {
    auto collector = collectors::anagrams_collector();
    collector.collect(data_vector, container, position + 1);

    for (auto it : collector.getAnagrams()) {
        output_stream << "Word: '" << it.first << "' Anagrams: ";
        if (!it.second.empty())
            utility::print_container(it.second, output_stream);
        else output_stream << "Anagrams not found\n";
    }
}

void containers::enhanced_vector::print_palindromes(containers::argument_container &container, int position) {
    auto collector = collectors::palindromes_collector();
    collector.collect(data_vector, container, position + 1);
    utility::print_container(collector.getPalindromes(), output_stream);
}

containers::enhanced_vector::enhanced_vector(std::vector<std::string> &dataVector,
                                             stream_helper &outputStream) : data_vector(dataVector),
                                                                            output_stream(outputStream) {}

std::vector<std::string> &containers::enhanced_vector::getDataVector() {
    return data_vector;
}

containers::enhanced_vector::~enhanced_vector() = default;




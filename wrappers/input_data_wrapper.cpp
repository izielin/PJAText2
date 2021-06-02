#include <iostream>
#include <utility>

#include "input_data_wrapper.h"
#include "../utils/utility_functions.h"
#include "../counters/counters.h"
#include "../collectors/anagrams_collector.h"
#include "../collectors/palindromes_collector.h"


void wrappers::input_data_wrapper::print_digits_amount() {
    auto counter = counters::digit_counter();
    counter.count(data_vector);
    output_stream << counter.get_amount() << '\n';
}

void wrappers::input_data_wrapper::print_numbers_amount() {
    auto counter = counters::number_counter();
    counter.count(data_vector);
    output_stream << counter.get_amount() << '\n';
}

void wrappers::input_data_wrapper::print_chars_amount(int position) {
    auto it = arguments.reverse_find_path(position); // search last loaded file path before flag
    if (it != arguments.getArguments().rend()) {
        auto counter = counters::char_counter();
        counter.count(*it);
        output_stream << counter.get_amount() << '\n';
    }
}

void wrappers::input_data_wrapper::print_word_amount() {
    output_stream << data_vector.size() << '\n';
}

void wrappers::input_data_wrapper::sort_alphabetically(int position) {
    if (arguments[position - 1] == "-l")
        input_data_wrapper::sort([](std::string &a, std::string &b) { return a.length() < b.length(); });
    else
        input_data_wrapper::sort([](std::string &a, std::string &b) { return a < b; });
}

void wrappers::input_data_wrapper::sort_reverse_alphabetically(int position) {
    if (arguments[position - 1] == "-l")
        input_data_wrapper::sort([](std::string &a, std::string &b) { return b.length() < a.length(); });
    else
        input_data_wrapper::sort([](std::string &a, std::string &b) { return b < a; });
}

void wrappers::input_data_wrapper::print_anagrams(int position) {
    auto collector = collectors::anagrams_collector();
    collector.collect(data_vector, arguments, position + 1);

    for (const auto &it : collector.getAnagrams()) {
        output_stream << "Word: '" << it.first << "' Anagrams: ";
        if (!it.second.empty())
            utility::print_container(it.second, output_stream);
        else output_stream << "Anagrams not found\n";
    }
}

void wrappers::input_data_wrapper::print_palindromes(int position) {
    auto collector = collectors::palindromes_collector();
    collector.collect(data_vector, arguments, position + 1);
    utility::print_container(collector.getPalindromes(), output_stream);
}

std::vector<std::string> &wrappers::input_data_wrapper::getDataVector() {
    return data_vector;
}

wrappers::input_data_wrapper::input_data_wrapper(wrappers::arguments_wrapper &arguments,
                                                 std::vector<std::string> dataVector,
                                                 stream_helper &outputStream)
        : arguments(arguments), data_vector(std::move(dataVector)), output_stream(outputStream) {}


wrappers::input_data_wrapper::~input_data_wrapper() = default;

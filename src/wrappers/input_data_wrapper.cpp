#include <iostream>

#include "../../include/wrappers/input_data_wrapper.h"
#include "../../include/utils/utility_functions.h"
#include "../../tools/include/collectors/anagrams_collector.h"
#include "../../tools/include/collectors/palindromes_collector.h"
#include "../../tools/include/counters/digit_counter.h"
#include "../../tools/include/counters/number_counter.h"
#include "../../tools/include/counters/char_counter.h"

/**
 * Constructor of input_data_wrapper
 * @param outputStream - instance of the stream_helper specifying the stream on which the data should be returned
 */
wrappers::input_data_wrapper::input_data_wrapper(stream_helper &outputStream)
        : _output_stream(outputStream) {}

std::vector<std::string> &wrappers::input_data_wrapper::getDataVector() {
    return _data_vector;
}

wrappers::input_data_wrapper::~input_data_wrapper() = default;

/**
 * Print number of digits stored in input_data_wrapper
 */
void wrappers::input_data_wrapper::print_number_of_digits() {
    auto counter = counters::digit_counter();
    counter.count(_data_vector);
    _output_stream << "Number of digits: " << counter.amount() << '\n';
}

/**
 * Print number of numbers stored in input_data_wrapper
 */
void wrappers::input_data_wrapper::print_number_of_numbers() {
    auto counter = counters::number_counter();
    counter.count(_data_vector);
    _output_stream << "Number of numbers: " << counter.amount() << '\n';
}

/**
 * Print number of chars in the file with the given path.
 * @param path_to_file - path to the file to be opened
 * @return number of chars in file with the given path
 */
void wrappers::input_data_wrapper::print_number_of_chars() {
    auto counter = counters::char_counter();
    counter.count(_data_vector);
    _output_stream << "Number of chars: " << counter.amount() << '\n';
}

/**p
 * Print number of words stored in input_data_wrapper
 */
void wrappers::input_data_wrapper::print_number_of_words() {
    _output_stream << "Number of words: " << _data_vector.size() << '\n';
}

/**
 * Sort data stored in input_data_wrapper in alphabetic order or by word length (longest to shortest) if the program was invoked with the '-l' flag
 * @param position - position of the flag against which we want to search the argument list
 */
void wrappers::input_data_wrapper::sort_alphabetically(int position) {
    if (_arguments->args_vector()[position - 1] == "-l") {
        _output_stream << "Sorted by length in ascending order: " << '\n';
        input_data_wrapper::sort([](std::string &a, std::string &b) { return a.length() < b.length(); });
    } else {
        _output_stream << "Sorted in alphabetic order: " << '\n';
        input_data_wrapper::sort([](std::string &a, std::string &b) { return a < b; });
    }
}

/**
 * Sort data stored in input_data_wrapper in reverse alphabetical order of by word length (from shortest to longest) if the program was invoked with the '-l' flag
 * @param position - position of the flag against which we want to search the argument list
 */
void wrappers::input_data_wrapper::reverse_sort_alphabetically(int position) {
    if (_arguments->args_vector()[position - 1] == "-l") {
        _output_stream << "Sorted by length in descending order: " << '\n';
        input_data_wrapper::sort([](std::string &a, std::string &b) { return b.length() < a.length(); });
    } else {
        _output_stream << "Sorted in reverse alphabetic order: " << '\n';
        input_data_wrapper::sort([](std::string &a, std::string &b) { return b < a; });
    }
}

/**
 * Print all words stored in input_data_wrapper which are anagrams of words given as _arguments to the program invocation
 * @param position - position of the flag against which we want to search the argument list
 */
void wrappers::input_data_wrapper::print_anagrams(int position) {
    auto collector = collectors::anagrams_collector();
    collector.collect(_data_vector, position + 1);

    for (const auto &it : collector.anagrams()) {
        _output_stream << "Word: '" << it.first << "', anagrams: ";
        if (!it.second.empty())
            utility::print_container(it.second, _output_stream);
        else _output_stream << "Anagrams not found\n";
    }
}

/**
 * Print all words given as _arguments to the program invocation that are palindromes and appear input_data_wrapper
 * @param position - position of the flag against which we want to search the argument list
 */
void wrappers::input_data_wrapper::print_palindromes(int position) {
    auto collector = collectors::palindromes_collector();
    collector.collect(_data_vector, position + 1);
    std::cout << "Palindromes: ";
    utility::print_container(collector.palindromes(), _output_stream);
}
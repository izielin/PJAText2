#ifndef PJATEXT2_INPUT_DATA_WRAPPER_H
#define PJATEXT2_INPUT_DATA_WRAPPER_H

#include <iostream>
#include <vector>
#include "../stream/stream_helper.h"
#include "arguments_wrapper.h"

namespace wrappers {
    class input_data_wrapper {
    private:
        wrappers::arguments_wrapper *_arguments = wrappers::arguments_wrapper::getInstance();
        std::vector<std::string> _data_vector = std::vector<std::string>();
        stream_helper &_output_stream;

        template<typename F>
        void sort(F predicate);

    public:
        input_data_wrapper(stream_helper &outputStream);

        std::vector<std::string> &getDataVector();

        ~input_data_wrapper();

        void print_number_of_digits();

        void print_number_of_numbers();

        void print_number_of_chars();

        void print_number_of_words();

        void sort_alphabetically(int position);

        void reverse_sort_alphabetically(int position);

        void print_anagrams(int position);

        void print_palindromes(int position);
    };
}

#include "input_data_wrapper.tpp"

#endif

#ifndef PJATEXT2_INPUT_DATA_WRAPPER_H
#define PJATEXT2_INPUT_DATA_WRAPPER_H

#include <iostream>
#include <vector>
#include "../utils/stream_helper.h"
#include "../wrappers/arguments_wrapper.h"

namespace wrappers {
    class input_data_wrapper {
    private:
        wrappers::arguments_wrapper arguments;
        std::vector<std::string> data_vector;
        stream_helper output_stream;

        template<typename F>
        void sort(F predicate);

    public:

        input_data_wrapper(arguments_wrapper &arguments, std::vector<std::string> dataVector,
                           stream_helper &outputStream);

        std::vector<std::string> &getDataVector();

        void print_digits_amount();

        void print_numbers_amount();

        void print_chars_amount(int position);

        void print_word_amount();

        void sort_alphabetically(int position);

        void sort_reverse_alphabetically(int position);

        void print_anagrams(int position);

        void print_palindromes(int position);

        virtual ~input_data_wrapper();
    };
}

#include "input_data_wrapper.tpp"

#endif

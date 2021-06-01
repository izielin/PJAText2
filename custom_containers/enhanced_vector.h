//
// Created by mmich on 01.06.2021.
//

#ifndef PJATEXT2_ENHANCED_VECTOR_H
#define PJATEXT2_ENHANCED_VECTOR_H

#include <iostream>
#include <vector>
#include "../utils/stream_helper.h"
#include "argument_container.h"

namespace containers {
    class enhanced_vector {
        std::vector<std::string> data_vector;
        stream_helper output_stream;

        template<typename F>
        void sort(F predicate);

    public:

        enhanced_vector(std::vector<std::string> &dataVector, stream_helper &outputStream);

        std::vector<std::string> &getDataVector();

        void print_digits_amount();

        void print_numbers_amount();

        void print_chars_amount(containers::argument_container &container, int position);

        void print_word_amount();

        void sort_alphabetically(containers::argument_container &container, int position);

        void sort_reverse_alphabetically(containers::argument_container &container, int position);

        void print_anagrams(containers::argument_container &container, int position);

        void print_palindromes(containers::argument_container &container, int position);

        virtual ~enhanced_vector();
    };
}

#include "enhanced_vector.tpp"

#endif //PJATEXT2_ENHANCED_VECTOR_H

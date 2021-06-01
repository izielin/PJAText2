//
// Created by mmich on 31.05.2021.
//

#include <iostream>
#include <algorithm>

#include "invoke_functions.h"
#include "utility_functions.h"
#include "../collectors/anagrams_collector.h"
#include "../counters/counters.h"
#include "../collectors/palindromes_collector.h"
#include "../custom_containers/enhanced_vector.h"

/*void m_flag(args_vector &container, int position, stream_helper &output_stream) {
    auto predicate = [](std::string &s) { return (s[0] != '-' && (&s)[-1] == "-f"); };

    auto it = reverse_find(arguments_vector, position, predicate);
    if (it != arguments_vector.rend()) // if path found
        if (arguments_vector[position - 1] != "-l")

                else

}*/

void invoke::invoke_functions(containers::argument_container &arguments_vector, stream_helper &output_stream) {
    auto vec = std::vector<std::string>();
    containers::enhanced_vector enhancedVector(vec, output_stream);

    for (int i = 0; i < arguments_vector.getArguments().size(); i++) {
        if (arguments_vector[i][0] != '-') continue; // skip file path

        if (arguments_vector[i] == "-f")
            utility::load_file_by_words(enhancedVector, arguments_vector[i + 1]);

        else if (arguments_vector[i] == "-n") {
            auto it = arguments_vector.reverse_find_path(i);
            if (it != arguments_vector.getArguments().rend()) // if path found
                utility::count_lines_in_file(*it, output_stream);
        } else if (arguments_vector[i] == "-d")
            enhancedVector.print_digits_amount();

        else if (arguments_vector[i] == "-dd")
            enhancedVector.print_numbers_amount();

        else if (arguments_vector[i] == "-c")
            enhancedVector.print_chars_amount(arguments_vector, i);

        else if (arguments_vector[i] == "-w")
            enhancedVector.print_word_amount();

        else if (arguments_vector[i] == "-s") {
            enhancedVector.sort_alphabetically(arguments_vector, i);
            utility::print_container(enhancedVector.getDataVector(), output_stream);
        } else if (arguments_vector[i] == "-rs") {
            enhancedVector.sort_reverse_alphabetically(arguments_vector, i);
            utility::print_container(enhancedVector.getDataVector(), output_stream);
        } else if (arguments_vector[i] == "-a")
            enhancedVector.print_anagrams(arguments_vector, i);

        else if (arguments_vector[i] == "-p")
            enhancedVector.print_palindromes(arguments_vector, i);
        /*else if (arguments_vector[i] == "-m")
            m_flag(arguments_vector, i, output_stream);*/
    }
}
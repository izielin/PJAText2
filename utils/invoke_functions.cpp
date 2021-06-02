#include <iostream>
#include <algorithm>

#include "invoke_functions.h"
#include "utility_functions.h"

void m_flag(wrappers::arguments_wrapper &arguments_vector, stream_helper &output_stream,
            std::vector<std::string>::iterator i) {
    int index = i - arguments_vector.getArguments().begin();
    auto vec = arguments_vector.return_paths(index + 1);
    utility::print_container(vec, output_stream);
    utility::merge_files(vec, arguments_vector[index - 1]);
}

void invoke::invoke_functions(wrappers::arguments_wrapper &arguments_vector, stream_helper &output_stream) {
    auto vec = std::vector<std::string>();
    wrappers::input_data_wrapper wrapper(arguments_vector, vec, output_stream);

    auto b = std::find(arguments_vector.getArguments().begin(),
                       arguments_vector.getArguments().end(), "-m");
    if (b != arguments_vector.getArguments().end())
        m_flag(arguments_vector, output_stream, b);

    for (int i = 0; i < arguments_vector.getArguments().size(); i++) {
        if (arguments_vector[i][0] != '-') continue; // skip file path

        if (arguments_vector[i] == "-f")
            utility::load_file_by_words(wrapper, arguments_vector[i + 1]);

        else if (arguments_vector[i] == "-n") {
            auto it = arguments_vector.reverse_find_path(i);
            if (it != arguments_vector.getArguments().rend()) // if path found
                utility::count_lines_in_file(*it, output_stream);
        } else if (arguments_vector[i] == "-d")
            wrapper.print_digits_amount();

        else if (arguments_vector[i] == "-dd")
            wrapper.print_numbers_amount();

        else if (arguments_vector[i] == "-c")
            wrapper.print_chars_amount(i);

        else if (arguments_vector[i] == "-w")
            wrapper.print_word_amount();

        else if (arguments_vector[i] == "-s") {
            wrapper.sort_alphabetically(i);
            utility::print_container(wrapper.getDataVector(), output_stream);
        } else if (arguments_vector[i] == "-rs") {
            wrapper.sort_reverse_alphabetically(i);
            utility::print_container(wrapper.getDataVector(), output_stream);
        } else if (arguments_vector[i] == "-a")
            wrapper.print_anagrams(i);

        else if (arguments_vector[i] == "-p")
            wrapper.print_palindromes(i);

    }
}
#include <iostream>
#include <algorithm>

#include "../../include/utils/run_function.h"
#include "../../include/utils/utility_functions.h"

/**
 * Call function merging the base file to ones after the -m flag
 * @param position - position of the flag against which we want to search the argument list
 */
void invoke_merge(int position) {
    auto paths = arguments->get_paths(position + 1);
    utility::merge_files(paths, arguments->args_vector()[position - 1]);
}

/**
 * Call the functionality of individual flags given as _arguments to call the program
 * @param output_stream - stream the result should be returned to
 */
void run(stream_helper &output_stream) {
    wrappers::input_data_wrapper wrapper(output_stream);

    auto m_flag_position = std::find(arguments_vector.begin(), arguments_vector.end(), "-m");
    if (m_flag_position != arguments_vector.end())
        invoke_merge(std::distance(arguments_vector.begin(), m_flag_position));

    for (auto iterator = arguments_vector.begin(); iterator != arguments_vector.end(); ++iterator) {
        auto i = std::distance(arguments_vector.begin(), iterator);

        if (iterator->front() != '-') continue; // skip file path

        if (*iterator == "-f")
            utility::load_file_by_words(wrapper.getDataVector(), *(iterator + 1));

        else if (*iterator == "-n") {
            auto it = arguments->reverse_find_path(iterator);
            if (it != arguments_vector.rend()) // if path found
                output_stream << "In file: " << *it
                              << " there are " << utility::count_lines_in_file(*it, output_stream) << " lines\n";

        } else if (*iterator == "-d")
            wrapper.print_number_of_digits();

        else if (*iterator == "-dd")
            wrapper.print_number_of_numbers();

        else if (*iterator == "-c") {
            wrapper.print_number_of_chars();

        } else if (*iterator == "-w")
            wrapper.print_number_of_words();

        else if (*iterator == "-s") {
            wrapper.sort_alphabetically(i);
            utility::print_container(wrapper.getDataVector(), output_stream);

        } else if (*iterator == "-rs") {
            wrapper.reverse_sort_alphabetically(i);
            utility::print_container(wrapper.getDataVector(), output_stream);

        } else if (*iterator == "-a")
            wrapper.print_anagrams(i);

        else if (*iterator == "-p")
            wrapper.print_palindromes(i);
    }
}
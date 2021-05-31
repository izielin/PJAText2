//
// Created by mmich on 31.05.2021.
//

#include <iostream>
#include <algorithm>

#include "invoke_functions.h"
#include "utility_functions.h"
#include "../global.h"
#include "../collectors/anagrams_collector.h"
#include "../counters/counters.h"
#include "../collectors/palindromes_collector.h"


void n_flag(arguments_container &container, int position, stream_helper &output_stream) {
    auto it = container.find_next_path(position);
    if (it != container.getArguments().rend()) // if path found
        utility::count_lines_in_file(*it, output_stream);
}

void d_flag(stream_helper &output_stream) {
    auto counter = counters::digit_counter();
    counter.count();
    output_stream << counter.get_amount() << '\n';
}

void dd_flag(stream_helper &output_stream) {
    auto counter = counters::number_counter();
    counter.count();
    output_stream << counter.get_amount() << '\n';
}

void c_flag(arguments_container &container, int position, stream_helper &output_stream) {
    auto it = container.find_next_path(position);
    if (it != container.getArguments().rend()) {
        auto counter = counters::char_counter();
        counter.count(*it);
        output_stream << counter.get_amount() << '\n';
    }
}

void s_flag(arguments_container &container, int position, stream_helper &output_stream) {
    if (container[position - 1] != "-l")
        std::sort(input_vector.begin(), input_vector.end());
    else
        std::sort(input_vector.begin(), input_vector.end(),
                  [](std::string &a, std::string &b) { return a.length() < b.length(); });
    utility::print_container(input_vector, output_stream);
}

void rs_flag(arguments_container &container, int position, stream_helper &output_stream) {
    if (container[position - 1] != "-l")
        std::sort(input_vector.begin(), input_vector.end(),
                  [](std::string &a, std::string &b) { return b < a; });
    else
        std::sort(input_vector.begin(), input_vector.end(),
                  [](std::string &a, std::string &b) { return b.length() < a.length(); });
    utility::print_container(input_vector, output_stream);
}

void a_flag(arguments_container &container, int position, stream_helper &output_stream) {
    auto collector = collectors::anagrams_collector();
    collector.collect(container, position + 1);

    for (auto it : collector.getAnagrams()) {
        output_stream << "Word: " << it.first << " Anagrams: ";
        utility::print_container(it.second, output_stream);
    }
}

void p_flag(arguments_container &container, int position, stream_helper &output_stream) {
    auto collector = collectors::palindromes_collector();
    collector.collect(container, position + 1);
    utility::print_container(collector.getPalindromes(), output_stream);
}

/*void m_flag(arguments_container &container, int position, stream_helper &output_stream) {
    auto predicate = [](std::string &s) { return (s[0] != '-' && (&s)[-1] == "-f"); };

    auto it = reverse_find(arguments_vector, position, predicate);
    if (it != arguments_vector.rend()) // if path found
        if (arguments_vector[position - 1] != "-l")

                else

}*/

void invoke::invoke_functions(arguments_container &arguments_vector, stream_helper &output_stream) {
    for (int i = 0; i < arguments_vector.getArguments().size(); i++) {
        if (arguments_vector[i][0] != '-') continue; // skip file path

        if (arguments_vector[i] == "-f")
            utility::load_file_by_words(arguments_vector[i + 1]);

        else if (arguments_vector[i] == "-n")
            n_flag(arguments_vector, i, output_stream);

        else if (arguments_vector[i] == "-d")
            d_flag(output_stream);

        else if (arguments_vector[i] == "-dd")
            dd_flag(output_stream);

        else if (arguments_vector[i] == "-c")
            c_flag(arguments_vector, i, output_stream);

        else if (arguments_vector[i] == "-w")
            output_stream << input_vector.size() << '\n';

        else if (arguments_vector[i] == "-s")
            s_flag(arguments_vector, i, output_stream);

        else if (arguments_vector[i] == "-rs")
            rs_flag(arguments_vector, i, output_stream);

        else if (arguments_vector[i] == "-a")
            a_flag(arguments_vector, i, output_stream);

        else if (arguments_vector[i] == "-p")
            p_flag(arguments_vector, i, output_stream);
        /*else if (arguments_vector[i] == "-m")
            m_flag(arguments_vector, i, output_stream);*/
    }
}
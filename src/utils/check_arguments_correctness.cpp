#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <fstream>
#include <array>
#include <sstream>

#include "../../include/utils/check_arguments_correctness.h"
#include "../../include/utils/utility_functions.h"
#include "../../include/utils/run_function.h"

/**
 * Define the stream to which program operation values should be returned. If -o flag appears on
 * arguments list the results will be returned to the stream writing data to the file with the given path,
 * otherwise to the stream writing data to the console.
 * @param output_file - path to file where result should be saved
 * @return stream to which the program operation values are to be returned
 */
auto define_output_stream(std::ofstream &output_file) {
    auto it = std::find(arguments_vector.begin(), arguments_vector.end(), "-o");
    if (it != arguments_vector.end()) {
        output_file.open(*(it + 1), std::ios::app | std::ios::out);
        if (!output_file) std::cerr << "Unable to open file, check if file path is correct";
        stream_helper helper(output_file);
        return helper;
    }
    stream_helper helper(std::cout);
    return helper;
}

/**
 * Check if the -i flag was called correctly. If no raise appropriate exception.
 * @param flag_properties - map that stores flags, flag aliases, and error text
 */
void check_i_flag_conditions(flag_properties_map &flag_properties) {
    if (arguments_vector[0] == "-i") {
        if (arguments_vector.size() == 1) {
            throw std::logic_error("The path to the file was not specified.");
        } else if (arguments_vector.size() == 2 && arguments_vector[1][0] != '-') {
            std::string path = arguments_vector[1];
            auto tem_vec = std::vector<std::string>();
            utility::load_file_by_words(tem_vec, path);
            arguments->set_args_vector(tem_vec);
        } else {
            throw std::logic_error(flag_properties["-i"].second);
        }
    }
}

/**
 * Check if the -m flag was called correctly. If no raise appropriate exception.
 * @param flag_properties - map that stores flags, flag aliases, and error text
 * @param position - position of the flag against which we want to search the argument list
 */
void check_m_flag_conditions(flag_properties_map &flag_properties, std::vector<std::string>::iterator position) {
    if ((position + 1) >= arguments_vector.end() || (position + 1)->front() == '-')
        throw std::logic_error("The path to the output file was not specified. Correct usage: '-m [file path]'");

    auto it = arguments->previous_flag_position(position);
    if (it == arguments_vector.rend() || *it != "-f")
        throw std::logic_error(flag_properties[*position].second);
}

/**
 * Check if the flag on given position is the last one. If no raise appropriate exception.
 * @param flag_properties - map that stores flags, flag aliases, and error text
 * @param position - position of the flag against which we want to search the argument list
 * @param exist - bool value determine if -f flag was passed
 */
void check_if_last_flags(flag_properties_map flag_properties, int position, bool exist) {
    if (!exist)
        throw std::logic_error("The path to the file was not specified.");
    else {
        auto &&predicate = [](std::string &s) { return (s[0] == '-'); };
        auto it = arguments->forward_find(position + 1, predicate);
        if (it != arguments->args_vector().end()) // if path found
            throw std::logic_error(flag_properties[arguments->args_vector()[position]].second);
    }
}

/**
 * Validates all passed flags
 * @param flag_properties - map that stores flags, flag aliases, and error text
 */
void check_flags_conditions(flag_properties_map &flag_properties) {

    std::vector<std::string> dependent_on_flag_f = {"-n", "-d", "-dd", "-c", "-w", "-s", "-rs"};
    bool f_flag_exist = false;
    for (auto iterator = arguments_vector.begin(); iterator != arguments_vector.end(); ++iterator) {
        auto pos = std::distance(arguments_vector.begin(), iterator);

        if (iterator->front() != '-') continue;

        if (*iterator == "-f" || *iterator == "-o") {
            if (arguments_vector.size() < 2 || (iterator + 1)->front() == '-')
                throw std::logic_error(flag_properties[*iterator].second);
            else f_flag_exist = true;

        } else {
            auto b = std::find(dependent_on_flag_f.begin(), dependent_on_flag_f.end(), *iterator) !=
                     dependent_on_flag_f.end();
            if (b) {
                if (!f_flag_exist)
                    throw std::logic_error(flag_properties[*iterator].second);

            } else if (*iterator == "-a" || *iterator == "-p") {
                check_if_last_flags(flag_properties, pos, f_flag_exist);

            } else if (*iterator == "-m") {
                check_m_flag_conditions(flag_properties, iterator);

            } else if (flag_properties.find(*iterator) == flag_properties.end()) {
                throw std::logic_error("The wrong flag or its alias was specified.\n"
                                       "Check the list of collected_words passed or call the application with the alias "
                                       "'--help' for more information. ");
            }
        }
    }
}

/**
 * Prints the manual of the program to the terminal
 */
void load_manual() {
    auto in = utility::open_file_to_read("../data/help_sheet.txt");
    for (auto line = std::string(); std::getline(in, line);)
        std::cout << line << '\n';
}

/**
 * Load flags, flag aliases, and error text from file with given path
 * @param path - path to the file to be opened
 * @return map that stores flag properties
 */
flag_properties_map load_flags_properties(std::string &path) {
    auto map = flag_properties_map();
    auto in = utility::open_file_to_read(path);

    std::string substr, line;
    std::vector<std::string> vec = {};

    for (; std::getline(in, line);) {
        std::stringstream ss(line);

        for (; getline(ss, substr, ';');)
            vec.push_back(substr);

        map[vec[0]] = std::make_pair(vec[1], vec[2]);
        vec.clear();
    }
    return map;
}

/**
 * Run check flags correctness functionality.
 */
void check_arguments_correctness() {
    std::string path = "../data/flag_properties.txt";
    auto flag_properties = load_flags_properties(path);

    if (arguments->args_vector().empty() || arguments->args_vector()[0] == "--help") {
        load_manual();
        return;
    }

    try {
        check_i_flag_conditions(flag_properties);
        arguments->adjust_arguments(flag_properties);
        check_flags_conditions(flag_properties);
    } catch (std::logic_error &logic_error) {
        std::cerr << logic_error.what() << '\n';
        return;
    }

    std::ofstream output_file;
    auto helper = define_output_stream(output_file);
    run(helper);
}


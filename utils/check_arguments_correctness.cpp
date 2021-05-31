//
// Created by mmich on 30.05.2021.
//

#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <fstream>
#include <array>
#include <sstream>

#include "check_arguments_correctness.h"
#include "utility_functions.h"
#include "invoke_functions.h"
#include "../custom_containers/container.h"

using flag_properties_map = std::map<std::string, std::pair<std::string, std::string>>;

namespace { //
    void adjust_vector(containers::argument_container &container, flag_properties_map &flag_properties) {

        auto &arguments_vector = container.getArguments();

        for (auto const&[key, val] : flag_properties)
            std::replace(arguments_vector.begin(), arguments_vector.end(), std::string(val.first), std::string(key));

        auto predicate = [](const std::string &a, const std::string &b) {
            return (a == b && (a == "-f" || a == "-l"));
        };
        arguments_vector.erase(
                std::unique(arguments_vector.begin(), arguments_vector.end(), predicate),
                arguments_vector.end());
    }


    auto define_output_stream(containers::argument_container &container, std::ofstream &output_file) {
        auto &arguments_vector = container.getArguments();

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

    void check_i_flag(containers::argument_container &container,
                      flag_properties_map &flag_properties) {
        if (container[0] == "-i") {
            if (container.getArguments().size() == 1) {
                throw std::logic_error("The path to the file was not specified.");  // -i was called but without path
            } else if (container.getArguments().size() == 2 && container[1][0] != '-') {
                std::string path = container[1];
                container.getArguments().clear();
                utility::load_file_by_line(container.getArguments(), path);
            } else {
                throw std::logic_error(flag_properties["-i"].second); // -i was called is not only flag
            }
        }
    }


    void check_last_flags(int position, containers::argument_container &container,
                          flag_properties_map flag_properties, bool exist) {
        if (!exist)
            throw std::logic_error("The path to the file was not specified.");
        else {
            // search for the last file path preceded by the -f flag
            auto &&predicate = [](std::string &s) { return (s[0] == '-'); };
            auto it = container.forward_find(position + 1, predicate);
            if (it != container.getArguments().end()) // if path found
                throw std::logic_error(flag_properties[container.getArguments()[position]].second);
        }
    }


    void
    check_loop(containers::argument_container &container, flag_properties_map &flag_properties) {
        std::vector<std::string> dependent_on_flag_f = {"-n", "-d", "-dd", "-c", "-w", "-s", "-rs"};
        bool f_flag_exist = false;
        for (int i = 0; i < container.getArguments().size(); i++) {
            if (container[i][0] != '-') continue; // skip file path

            if (container[i] == "-f") {
                if (container[i + 1][0] == '-')
                    throw std::logic_error(flag_properties["-f"].second); // -f was called but without path
                f_flag_exist = true;

            } else if (container[i] == "-o" || container[i] == "-m") {
                if (container[i + 1][0] == '-')
                    throw std::logic_error(
                            flag_properties[container[i + 1]].second); // -0 was called but without path

            } else if (std::find(dependent_on_flag_f.begin(), dependent_on_flag_f.end(), container[i]) !=
                       dependent_on_flag_f.end()) {
                if (!f_flag_exist)
                    throw std::logic_error(flag_properties[container[i]].second); // no path specified

            } else if (container[i] == "-a" || container[i] == "-p") {
                check_last_flags(i, container, flag_properties, f_flag_exist);
            } else {
                throw std::logic_error("The wrong flag or its alias was specified.\n"
                                       "Check the list of collected_words passed or call the application with the alias "
                                       "'--help' for more information. ");
            }
        }
    }
}

flag_properties_map load_flags_properties(std::string &path) {
    auto map = flag_properties_map();
    auto in = utility::open_file(path);

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

void check::check_arguments_correctness(containers::argument_container &arguments) {

    std::string path = "../inputs/flag_properties.txt";
    auto flag_properties = load_flags_properties(path);

    if (arguments.getArguments().empty()) {
        std::cout << "help" << '\n';
        return;
    }

    try {
        check_i_flag(arguments, flag_properties);
        adjust_vector(arguments, flag_properties);
        check_loop(arguments, flag_properties);
    } catch (std::logic_error &logic_error) { //Handle Any Type of Exceptions
        std::cerr << logic_error.what() << '\n';
        return;
    }

    std::ofstream output_file;
    auto helper = define_output_stream(arguments, output_file);
    invoke::invoke_functions(arguments, helper);
}
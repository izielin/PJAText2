//
// Created by mmich on 30.05.2021.
//

#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <fstream>

#include "check_arguments_correctness.h"
#include "utility_functions.h"
#include "../global.h"
#include "../counters/counters.h"
#include "../collectors/anagrams_collector.h"
#include "../collectors/palindromes_collector.h"

void adjust_vector(std::vector<std::string> &arguments_vector) {
    std::map<std::string, std::string> flag_aliases = {
            {"--file",           "-f"},
            {"--newlines",       "-n"},
            {"--digits",         "-d"},
            {"--numbers",        "-dd"},
            {"--chars",          "-c"},
            {"--words",          "-w"},
            {"--sorted",         "-s"},
            {"--reverse-sorted", "-rs"},
            {"--by-length",      "-l"},
            {"--anagrams",       "-a"},
            {"--output",         "-o"},
            {"--palindromes",    "-p"},
            {"--input",          "-i"}
//            {"--reverse-sorted", "-rs"} my flag
    };

    for (auto const&[key, val] : flag_aliases) {
        std::replace(arguments_vector.begin(), arguments_vector.end(), std::string(key), std::string(val));
    }

    arguments_vector.erase(
            std::unique(arguments_vector.begin(), arguments_vector.end(),
                        [](const std::string &a, const std::string &b) {
                            return (a == b && (a == "-f" || a == "-l"));
                        }), arguments_vector.end());
}


auto get_file_path(std::vector<std::string> &arguments_vector, int argument_index) {
    auto it = std::find_if(arguments_vector.rbegin() + (arguments_vector.size() - argument_index),
                           arguments_vector.rend(),
                           [](std::string &s) {
                               // search for the last file path preceded by the -f flag
                               return (s[0] != '-' && (&s)[-1] == "-f");
                           });
    return it;
}


auto search_flag_after_given_position(std::vector<std::string> &arguments_vector, int argument_index) {
    auto it = std::find_if(arguments_vector.begin() + argument_index,
                           arguments_vector.end(),
                           [](std::string &s) {
                               // search for the last file path preceded by the -f flag
                               return (s[0] == '-');
                           });
    return it;
}

void load_flags_from_file(std::vector<std::string> &vector, const std::string &path) {
    auto in = utility::open_file(path);


    for (auto line = std::string(); std::getline(in, line, ' ');) {
        if (std::all_of(line.begin(), line.end(), isspace)) continue; // ignore words contains only whitespaces
        utility::trim(line);
        vector.emplace_back(line);
    }

    in.close();
}


void invoke(std::vector<std::string> &arguments_vector, stream_helper &output_stream) {

    output_stream << 'a' << '\n';

    for (int i = 0; i < arguments_vector.size(); i++) {

        if (arguments_vector[i] == "-f") {
            utility::load_file(arguments_vector[i + 1]);
        } else if (arguments_vector[i] == "-n") {

            auto it = get_file_path(arguments_vector, i);
            if (it != arguments_vector.rend()) // if path found
                utility::count_lines_in_file(*it, output_stream);

        } else if (arguments_vector[i] == "-d") {
            auto counter = counters::digit_counter();
            counter.count();
            output_stream << counter.get_amount() << '\n';

        } else if (arguments_vector[i] == "-dd") {
            auto counter = counters::number_counter();
            counter.count();
            output_stream << counter.get_amount() << '\n';
        } else if (arguments_vector[i] == "-c") {
            auto it = get_file_path(arguments_vector, i);
            if (it != arguments_vector.rend()) {
                auto counter = counters::char_counter();
                counter.count(*it);
                output_stream << counter.get_amount() << '\n';
            }
        } else if (arguments_vector[i] == "-w") {
            output_stream << input_vector.size() << '\n';
        } else if (arguments_vector[i] == "-s") {
            if (arguments_vector[i - 1] != "-l")
                std::sort(input_vector.begin(), input_vector.end());
            else
                std::sort(input_vector.begin(), input_vector.end(),
                          [](std::string &a, std::string &b) { return a.length() < b.length(); });
            utility::print_container(input_vector, output_stream);
        } else if (arguments_vector[i] == "-rs") {
            if (arguments_vector[i - 1] != "-l")
                std::sort(input_vector.begin(), input_vector.end(),
                          [](std::string &a, std::string &b) { return b < a; });
            else
                std::sort(input_vector.begin(), input_vector.end(),
                          [](std::string &a, std::string &b) { return b.length() < a.length(); });
            utility::print_container(input_vector, output_stream);
        } else if (arguments_vector[i] == "-a") {


            auto collector = collectors::anagrams_collector();
            collector.collect(arguments_vector, i + 1);

            for (auto it : collector.getAnagrams()) {
                output_stream << "Word: " << it.first << " Anagrams: ";
                utility::print_container(it.second, output_stream);
            }
        } else if (arguments_vector[i] == "-p") {

            auto collector = collectors::palindromes_collector();
            collector.collect(arguments_vector, i + 1);
            utility::print_container(collector.getPalindromes(), output_stream);

        }

    }
}


auto define_output_stream(std::vector<std::string> &arguments_vector, std::ofstream &output_file) {
    auto it = std::find(arguments_vector.begin(), arguments_vector.end(), "-o");

    if (it != arguments_vector.end()) {
        output_file.open(*(it + 1), std::ios::app | std::ios::out);
        if (!output_file) std::cerr << "Unable to open file, check if file path is correct";

        stream_helper helper(output_file);

        helper << 'b';

        return helper;
    }
    stream_helper helper(std::cout);
    helper << 'c';

    return helper;

}


void check::check_arguments_correctness(std::vector<std::string> &arguments_vector) {

    if (arguments_vector.empty()) {
        std::cout << "help" << '\n';
        return;
    }

    if (arguments_vector[0] == "-i") {
        if (arguments_vector.size() == 1) {
            // -i was called but without path
            throw std::logic_error("The path to the file was not specified. Correct usage: '-i [file path]'");
        } else if (arguments_vector.size() > 2 || arguments_vector[1][0] == '-') {
            throw std::logic_error("should be only flag");
        } else {
            std::string path = arguments_vector[1];
            arguments_vector.clear();
            load_flags_from_file(arguments_vector, path);

        }
    }


    adjust_vector(arguments_vector);
    bool f_flag_exist = false;

    for (int i = 0; i < arguments_vector.size(); i++) {
        try {
            if (arguments_vector[i][0] != '-') continue; // skip file path

            // -f flag

            if (arguments_vector[i] == "-f") {
                if (arguments_vector[i + 1][0] == '-')
                    // -f was called but without path
                    throw std::logic_error("The path to the file was not specified. Correct usage: '-f [file path]'");
                else
                    f_flag_exist = true;
            }

            if (arguments_vector[i] == "-o") {
                if (arguments_vector[i + 1][0] == '-')
                    // -f was called but without path
                    throw std::logic_error("The path to the file was not specified. Correct usage: '-o [file path]'");
                else
                    f_flag_exist = true;
            }
                // -n flag

            else if (arguments_vector[i] == "-n") {
                if (!f_flag_exist)
                    std::cerr << "The path to the file from which lines should be "
                                 "count was not specified. Correct usage: '-f [file path] -n'\n";

            } else if (arguments_vector[i] == "-d") {
                if (!f_flag_exist)
                    std::cerr << "Correct usage: '-f [file path] -d'\n";

            } else if (arguments_vector[i] == "-dd") {
                if (!f_flag_exist)
                    std::cerr << "Correct usage: '-f [file path] -dd'\n";

            } else if (arguments_vector[i] == "-c") {
                if (!f_flag_exist)
                    std::cerr << "Correct usage: '-f [file path] -c'\n";

            } else if (arguments_vector[i] == "-w") {
                if (!f_flag_exist)
                    std::cerr << "Correct usage: '-f [file path] -w'\n";

            } else if (arguments_vector[i] == "-s") {
                if (!f_flag_exist)
                    throw std::logic_error(
                            "The path to the file was not specified. Correct usage: '-f [file path] -s'");

            } else if (arguments_vector[i] == "-rs") {
                if (!f_flag_exist)
                    std::cerr << "Correct usage: '-f [file path] -rs'\n";

            } else if (arguments_vector[i] == "-a") {
                if (!f_flag_exist)
                    std::cerr << "Correct usage: '-f [file path] -a'\n";
                else {
                    auto it = search_flag_after_given_position(arguments_vector, i + 1);

                    if (it != arguments_vector.end()) // if path found
                        throw std::logic_error("-a should be last used flag");
                }

            } else if (arguments_vector[i] == "-p") {
                if (!f_flag_exist)
                    std::cerr << "Correct usage: '-f [file path] -p'\n";
                else {
                    auto it = search_flag_after_given_position(arguments_vector, i + 1);
                    if (it != arguments_vector.end()) // if path found
                        throw std::logic_error("-p should be last used flag");
                }
            }

        } catch (std::logic_error &logic_error) { //Handle Any Type of Exceptions
            std::cerr << logic_error.what() << '\n';
            return;
        }
    }

    std::ofstream output_file;
    auto helper = define_output_stream(arguments_vector, output_file);

    helper << 'd' << '\n';
    invoke(arguments_vector, helper);


}






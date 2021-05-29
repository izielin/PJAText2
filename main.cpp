//
// Created by mmich on 25.05.2021.
//

#include <iostream>
#include <algorithm>
#include <sstream>
#include <fstream>
#include <map>
#include <ctime>

#include "counters.h"
#include "global.h"


// trim from start (in place)
static inline void ltrim(std::string &s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch) {
        return !std::isspace(ch);
    }));
}

// trim from end (in place)
static inline void rtrim(std::string &s) {
    s.erase(std::find_if(s.rbegin(), s.rend(), [](unsigned char ch) {
        return !std::isspace(ch);
    }).base(), s.end());
}

// trim from both ends (in place)
void trim(std::string &s) {
    ltrim(s);
    rtrim(s);
}

auto open_file(const std::string &path_to_file) {
    std::ifstream in(path_to_file);
    if (!in) std::cerr << "Unable to open file, check if file path is correct";
    else return in;
}

void load_file(std::vector<std::string> &vector, const std::string &path_to_file) {

    auto in = open_file(path_to_file);

    for (auto line = std::string(); std::getline(in, line);) {
        std::stringstream ss(line);
        for (auto word = std::string(); getline(ss, word, ' ');) {
            if (std::all_of(word.begin(), word.end(), isspace)) continue; // ignore words contains only whitespaces
            trim(word);
            input_vector.emplace_back(word);
        }
    }

    in.close();
}

void count_lines_in_file(std::string &path_to_file) {
    auto in = open_file(path_to_file);

    std::string line;
    long i;
    for (i = 0; std::getline(in, line); ++i);

    std::cout << "In file: " << path_to_file << " there are " << i << " lines\n";
    in.close();
}

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
//            {"--reverse-sorted", "-rs"}
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


auto getFilePath(std::vector<std::string> &arguments_vector, int argument_index) {
    auto it = std::find_if(arguments_vector.rbegin() + (arguments_vector.size() - argument_index),
                           arguments_vector.rend(),
                           [](std::string &s) {
                               // search for the last file path preceded by the -f flag
                               return (s[0] != '-' && (&s)[-1] == "-f");
                           });
    return it;
}

template<typename T>
void print_vector(const std::vector<T> &vec) {
    std::string separator = ", ";
    for (auto &&item : vec) {
        std::cout << item;
        if (&item != &vec.back()) std::cout << separator;
    }
    std::cout << '\n';
}


void check_arguments_correctness(std::vector<std::string> &arguments_vector) {

    adjust_vector(arguments_vector);
    bool f_flag_exist = false;
    if (arguments_vector.empty()) {
        std::cout << "help" << '\n';
        return;
    }


    for (int i = 0; i < arguments_vector.size(); i++) {
        try {


            if (arguments_vector[i][0] != '-') continue; // skip file path

            // -f flag

            if (arguments_vector[i] == "-f") {
                if (arguments_vector[i + 1][0] == '-') {
                    // -f was called but without path
                    throw std::logic_error("The path to the file was not specified. Correct usage: '-f [file path]'");
                } else {
                    load_file(input_vector, arguments_vector[i + 1]);
                    f_flag_exist = true;
                }
            }
                // -n flag

            else if (arguments_vector[i] == "-n") {
                if (!f_flag_exist)
                    std::cerr << "The path to the file from which lines should be "
                                 "count was not specified. Correct usage: '-f [file path] -n'\n";
                else {
                    auto it = getFilePath(arguments_vector, i);

                    if (it != arguments_vector.rend()) // if path found
                        count_lines_in_file(*it);
                }
            } else if (arguments_vector[i] == "-d") {
                if (!f_flag_exist)
                    std::cerr << "Correct usage: '-f [file path] -d'\n";
                else {
                    auto counter = counting_methods::digit_counter();
                    counter.count();
                    std::cout << counter.get_amount() << '\n';

                }

            } else if (arguments_vector[i] == "-dd") {
                if (!f_flag_exist)
                    std::cerr << "Correct usage: '-f [file path] -dd'\n";
                else {
                    auto counter = counting_methods::number_counter();
                    counter.count();
                    std::cout << counter.get_amount() << '\n';

                }

            } else if (arguments_vector[i] == "-c") {
                if (!f_flag_exist)
                    std::cerr << "Correct usage: '-f [file path] -dd'\n";
                else {

                    auto it = getFilePath(arguments_vector, i);
                    if (it != arguments_vector.rend()) {
                        auto counter = counting_methods::char_counter();
                        counter.count(*it);
                        std::cout << counter.get_amount() << '\n';
                    }

                }

            } else if (arguments_vector[i] == "-w") {
                if (!f_flag_exist)
                    std::cerr << "Correct usage: '-f [file path] -dd'\n";
                else {
                    std::cout << input_vector.size() << '\n';

                }

            } else if (arguments_vector[i] == "-s") {
                if (!f_flag_exist)
                    throw std::logic_error(
                            "The path to the file was not specified. Correct usage: '-f [file path] -s'");
                else {
                    if (arguments_vector[i - 1] != "-l")
                        std::sort(input_vector.begin(), input_vector.end());
                    else
                        std::sort(input_vector.begin(), input_vector.end(),
                                  [](std::string &a, std::string &b) { return a.length() < b.length(); });

                    print_vector(input_vector);
                }

            } else if (arguments_vector[i] == "-rs") {
                if (!f_flag_exist)
                    std::cerr << "Correct usage: '-f [file path] -dd'\n";
                else {

                    if (arguments_vector[i - 1] != "-l")
                        std::sort(input_vector.begin(), input_vector.end(),
                                  [](std::string &a, std::string &b) { return b < a; });
                    else
                        std::sort(input_vector.begin(), input_vector.end(),
                                  [](std::string &a, std::string &b) { return b.length() < a.length(); });
                    print_vector(input_vector);
                }

            }
        } catch (std::logic_error &logic_error) { //Handle Any Type of Exceptions
            std::cerr << logic_error.what() << '\n';
            break;
        }
    }

}

int main(int argc, char *argv[]) {

    auto arguments = std::vector<std::string>(argv + 1, argv + argc);

    check_arguments_correctness(arguments);

    return 0;
}



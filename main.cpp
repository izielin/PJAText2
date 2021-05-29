//
// Created by mmich on 25.05.2021.
//

#include <iostream>
#include <algorithm>
#include <sstream>
#include <fstream>
#include <map>
#include <set>
#include <cstring>

#include "counters.h"
#include "global.h"

#define NO_OF_CHARS 256

template<template<typename, typename...> class TT, typename Args>
void print_container(TT<Args> &container) {
    for (auto it = container.begin(); it != container.end(); ++it) {
        if (it != container.begin())
            std::cout << ", ";
        std::cout << *it;
    }
    std::cout << '\n';

}


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

    if (input_vector.size() != 0) input_vector.clear(); // clear vector if new file was loaded

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


auto collect_words(std::vector<std::string> &arguments_vector, int position) {
    std::set<std::string> words;

    for (auto iterator = arguments_vector.begin() + position;
         iterator != arguments_vector.end(); words.insert(*iterator++));

    return words;
}


/**
 * \brief Function check whether two strings are anagram of each other
 *
 * The function iterates over the given words. Increase the value in the count array
 * for the characters in str1 and decrease it for the characters in str2.
 * If the numbers are all 0, then these two strings are anagrams of each other.
 *
 * @param word_1
 * @param word_2
 * @return
 */

auto are_anagram(const std::string &word_1, const std::string &word_2) {
    int count[NO_OF_CHARS] = {0};

    // If strings have different length return false
    if (word_1.length() != word_2.length())
        return false;

    for (int i = 0; word_1[i] && word_2[i]; i++) {
        count[tolower(word_1[i])]++;
        count[tolower(word_2[i])]--;
    }

    // check if there is any non-zero value in array
    for (int i = 0; i < NO_OF_CHARS; i++)
        if (count[i])
            return false;
    return true;
}

bool is_palindrome(const std::string &word) {
    int l = 0, h = word.length() - 1;
    while (h > l)
        if (word[l++] != word[h--]) return false;
    return true;
}

auto search_anagrams(std::vector<std::string> &arguments_vector, int position) {

    auto words = collect_words(arguments_vector, position);

    std::map<std::string, std::set<std::string>> anagrams;
    std::set<std::string> matching_words;

    for (auto &&word : words) {
        for (auto &&item : input_vector) {
            if (are_anagram(word.c_str(), item.c_str())) {
                std::transform(item.begin(), item.end(), item.begin(),
                               [](unsigned char c) { return std::tolower(c); });
                matching_words.insert(item);
            }
        }
        anagrams.insert(std::make_pair(word, matching_words));
        matching_words.clear();
    }


    return anagrams;
}

auto search_palindromes(std::vector<std::string> &arguments_vector, int position) {

    auto words = collect_words(arguments_vector, position);

    std::set<std::string> matching_words;

    for (auto &&word : words) {
        if (is_palindrome(word) && std::find(input_vector.begin(), input_vector.end(), word) != input_vector.end()) {
            matching_words.insert(word);
        }
    }
    return matching_words;
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
                    auto it = get_file_path(arguments_vector, i);

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

                    auto it = get_file_path(arguments_vector, i);
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

                    print_container(input_vector);
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
                    print_container(input_vector);
                }

            } else if (arguments_vector[i] == "-a") {
                if (!f_flag_exist)
                    std::cerr << "Correct usage: '-f [file path] -dd'\n";

                else {

                    auto it = search_flag_after_given_position(arguments_vector, i + 1);

                    if (it != arguments_vector.end()) // if path found
                        throw std::logic_error("-a should be last used flag");


                    auto anagrams = search_anagrams(arguments_vector, i + 1);

                    for (auto it : anagrams) {
                        std::cout << "Word: " << it.first << " Anagrams: ";
                        print_container(it.second);
                    }
                }

            } else if (arguments_vector[i] == "-p") {
                if (!f_flag_exist)
                    std::cerr << "Correct usage: '-f [file path] -dd'\n";

                else {

                    auto it = search_flag_after_given_position(arguments_vector, i + 1);

                    if (it != arguments_vector.end()) // if path found
                        throw std::logic_error("-p should be last used flag");

                    auto palindromes = search_palindromes(arguments_vector, i + 1);

                    print_container(palindromes);


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



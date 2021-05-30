//
// Created by mmich on 30.05.2021.
//

#include <iostream>
#include <algorithm>
#include <sstream>
#include <fstream>

#include "utility_functions.h"
#include "../global.h"

// trim from start (in place)
void utility::ltrim(std::string &s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch) {
        return !std::isspace(ch);
    }));
}

// trim from end (in place)
void utility::rtrim(std::string &s) {
    s.erase(std::find_if(s.rbegin(), s.rend(), [](unsigned char ch) {
        return !std::isspace(ch);
    }).base(), s.end());
}

// trim from both ends (in place)
void utility::trim(std::string &s) {
    ltrim(s);
    rtrim(s);
}

std::ifstream utility::open_file(const std::string &path_to_file) {
    std::ifstream in(path_to_file);
    if (!in) std::cerr << "Unable to open file, check if file path is correct";
    else return in;
}

void utility::load_file(const std::string &path_to_file) {
    if (input_vector.size() != 0) input_vector.clear(); // clear vector if new file was loaded

    input_vector.emplace_back("a");

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

void utility::count_lines_in_file(std::string &path_to_file) {

    auto in = open_file(path_to_file);

    std::string line;
    long i;
    for (i = 0; std::getline(in, line); ++i);

    std::cout << "In file: " << path_to_file << " there are " << i << " lines\n";
    in.close();
}



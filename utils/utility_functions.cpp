//
// Created by mmich on 30.05.2021.
//

#include <iostream>
#include <algorithm>
#include <sstream>
#include <fstream>

#include "utility_functions.h"

// trim from start
void utility::ltrim(std::string &s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch) {
        return !std::isspace(ch);
    }));
}

// trim from end
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
    try {
        if (!in) throw std::logic_error("Unable to open file, check if file path is correct");
        else return in;
    } catch (std::logic_error e) {
        std::cerr << e.what() << '\n';
        exit(-1);
    }

}


void utility::load_file_by_words(containers::enhanced_vector &container, const std::string &path_to_file) {
    if (container.getDataVector().size() != 0) container.getDataVector().clear(); // clear vector if new file was loaded

    auto in = open_file(path_to_file);

    for (auto line = std::string(); std::getline(in, line);) {
        std::stringstream ss(line);
        for (auto word = std::string(); getline(ss, word, ' ');) {
            if (std::all_of(word.begin(), word.end(), isspace)) continue; // ignore words contains only whitespaces
            trim(word);
            container.getDataVector().emplace_back(word);
        }
    }
    in.close();
}

void utility::load_file_by_line(std::vector<std::string> &vector, const std::string &path) {
    auto in = open_file(path);

    for (auto line = std::string(); std::getline(in, line, ' ');) {
        if (std::all_of(line.begin(), line.end(), isspace)) continue; // ignore words contains only whitespaces
        utility::trim(line);
        vector.emplace_back(line);
    }

    in.close();
}

void utility::count_lines_in_file(std::string &path_to_file, stream_helper &output_stream) {
    auto in = open_file(path_to_file);

    std::string line;
    long i;
    for (i = 0; std::getline(in, line); ++i);

    output_stream << "In file: " << path_to_file << " there are " << i << " lines\n";
    in.close();
}



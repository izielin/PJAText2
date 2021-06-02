#include <iostream>
#include <algorithm>
#include <sstream>
#include <fstream>

#include "utility_functions.h"

std::string utility::trim(std::string &s) {
    size_t first = s.find_first_not_of(' ');
    if (std::string::npos == first) {
        return s;
    }
    size_t last = s.find_last_not_of(' ');
    return s.substr(first, (last - first + 1));
}

std::ifstream utility::open_file_to_read(const std::string &path_to_file) {
    std::ifstream in(path_to_file);
    try {
        if (!in) throw std::logic_error("Unable to open file, check if file path is correct");
        else return in;
    } catch (std::logic_error &e) {
        std::cerr << e.what() << '\n';
        exit(-1);
    }

}

std::ofstream utility::open_file_to_write(const std::string &path_to_file) {
    std::ofstream out(path_to_file, std::fstream::out | std::fstream::app);
    try {
        if (!out) throw std::logic_error("Unable to open file, check if file path is correct");
        else return out;
    } catch (std::logic_error &e) {
        std::cerr << e.what() << '\n';
        exit(-1);
    }

}


void utility::load_file_by_words(wrappers::input_data_wrapper &container, const std::string &path_to_file) {
    if (!container.getDataVector().empty()) container.getDataVector().clear();

    auto in = open_file_to_read(path_to_file);

    for (auto line = std::string(); std::getline(in, line);) {
        std::stringstream ss(line);
        for (auto word = std::string(); getline(ss, word, ' ');) {
            if (std::all_of(word.begin(), word.end(), isspace)) continue; // ignore words contains only whitespaces
            container.getDataVector().emplace_back(trim(word));
        }
    }
    in.close();
}

void utility::load_file_by_line(std::vector<std::string> &vector, const std::string &path) {
    auto in = open_file_to_read(path);

    for (auto line = std::string(); std::getline(in, line, ' ');) {
        if (std::all_of(line.begin(), line.end(), isspace)) continue; // ignore lines contains only whitespaces
        vector.emplace_back(utility::trim(line));
    }

    in.close();
}

void utility::count_lines_in_file(std::string &path_to_file, stream_helper &output_stream) {
    auto in = open_file_to_read(path_to_file);

    std::string line;
    long i;
    for (i = 0; std::getline(in, line); ++i);

    output_stream << "In file: " << path_to_file << " there are " << i << " lines\n";
    in.close();
}

void utility::merge_files(std::vector<std::string> &to_merge_path, std::string &base_path) {
    auto out = open_file_to_write(base_path);

    for (auto &item : to_merge_path) {
        auto in = open_file_to_read(item);
        out << '\n' << in.rdbuf();
        in.close();
    }
    out.close();

}



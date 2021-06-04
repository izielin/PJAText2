#include <iostream>
#include <algorithm>
#include <sstream>
#include <fstream>

#include "../../include/utils/utility_functions.h"

/**
 * Delete all whitespaces from front and back of passed string
 * @param input_string - string to trim_string
 * @return string without whitespaces
 */
std::string utility::trim_string(std::string &input_string) {
    size_t first = input_string.find_first_not_of(' ');
    if (std::string::npos == first) {
        return input_string;
    }
    size_t last = input_string.find_last_not_of(' ');
    return input_string.substr(first, (last - first + 1));
}

/**
 * Opens the file with the given path in read-only mode. In case of a wrong path, an exception will be raised.
 * @param path_to_file - path to the file to be opened
 * @return ifstream object if file could be opened
 */
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

/**
 * Opens the file with the given path in write-only mode. . In case of a wrong path, an exception will be raised.
 * @param path_to_file - path to the file to be opened
 * @return ifstream object if file could be opened
 */
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

/**
 * Reads the file word by word and writes to passed object of wrappers::input_data_wrapper.
 * @param vector - instance of wrappers::input_data_wrapper where read data should be saved
 * @param path_to_file - path to the file to be opened
 */
void utility::load_file_by_words(std::vector<std::string> &vector, const std::string &path_to_file) {
    if (!vector.empty()) vector.clear();

    auto in = open_file_to_read(path_to_file);

    for (auto line = std::string(); std::getline(in, line);) {
        std::stringstream ss(line);
        for (auto word = std::string(); getline(ss, word, ' ');) {
            if (std::all_of(word.begin(), word.end(), isspace)) continue;
            vector.emplace_back(trim_string(word));
        }
    }
    in.close();
}

/**
 * Count number of lines in the file with the given path.
 * @param path_to_file - path to the file to be opened
 * @param output_stream - stream the result should be returned to
 * @return number of lines in file with the given path
 */
int utility::count_lines_in_file(std::string &path_to_file, stream_helper &output_stream) {
    auto in = open_file_to_read(path_to_file);

    auto i = 0;
    for (auto line = std::string(); std::getline(in, line); ++i);

    in.close();
    return i;
}

/**
 * Copies the content from the files given in the vector and writes them to the end of the file with the given path
 * @param files_paths - paths to files to be linked to the base file
 * @param base_file_path - path to base file
 */
void utility::merge_files(std::vector<std::string> &files_paths, std::string &base_file_path) {
    auto out = open_file_to_write(base_file_path);
    for (auto &item : files_paths) {
        auto in = open_file_to_read(item);
        out << in.rdbuf() << '\n';
        in.close();
    }
    out.close();
}



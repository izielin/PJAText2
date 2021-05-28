//
// Created by mmich on 25.05.2021.
//

#include <iostream>
#include <algorithm>
#include <sstream>
#include <fstream>
#include <map>

inline auto input_vector = std::vector<std::string>();

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


void load_file(std::vector<std::string> &vector, const std::string &path_to_file) {
    std::string line;
    std::ifstream in(path_to_file);
    if (!in) {
        std::cerr << "Unable to open file, check if file path is correct";
        return;
    }

    while (std::getline(in, line, ' ')) {
        if (std::all_of(line.begin(), line.end(), isspace)) continue; // ignore words contains only whitespaces
        trim(line);
        input_vector.emplace_back(line);
    }

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
            {"--reverse-sorted", "-rs"}
    };

    for (auto const&[key, val] : flag_aliases) {
        std::replace(arguments_vector.begin(), arguments_vector.end(), std::string(key), std::string(val));
    }

    arguments_vector.erase(
            std::unique(arguments_vector.begin(), arguments_vector.end(), [](std::string a, std::string b) {
                return (a == b && (a == "-f" || a == "-l"));
            }), arguments_vector.end());
}

void check_arguments_correctness(std::vector<std::string> &arguments_vector) {

    adjust_vector(arguments_vector);

    for (int i = 0; i < arguments_vector.size(); i++) {

        if (arguments_vector[i][0] != '-') continue; // skip file path

        // load input file
        if (arguments_vector[i] == "-f" && arguments_vector[i + 1][0] == '-') {
            std::cerr << "usage: -f [file path]\n";
        } else {
            load_file(input_vector, arguments_vector[i + 1]);


        };
    }
}

int main(int argc, char *argv[]) {

    auto arguments = std::vector<std::string>(argv + 1, argv + argc);


    check_arguments_correctness(arguments);


    /* if (argc == 1) {
         std::cout << "H\n";
         return 0;
     }

     while (*++argv) {
         if ((*argv)[0] == '-') {
             if (strcmp(*argv, "--help") == 0) std::cout << "H\n";
             else if (strcmp(*argv, "--file") == 0 || strcmp(*argv, "-f") == 0) std::cout << "F\n";
             else if (strcmp(*argv, "--newlines") == 0 || strcmp(*argv, "-n") == 0) std::cout << "N\n";
             else if (strcmp(*argv, "--digits") == 0 || strcmp(*argv, "-position") == 0) std::cout << "D\n";
             else if (strcmp(*argv, "--numbers") == 0 || strcmp(*argv, "-dd") == 0) std::cout << "N\n";
             else if (strcmp(*argv, "--chars") == 0 || strcmp(*argv, "-c") == 0) std::cout << "C\n";
             else if (strcmp(*argv, "--words") == 0 || strcmp(*argv, "-w") == 0) std::cout << "W\n";
             else if (strcmp(*argv, "--sorted") == 0 || strcmp(*argv, "-s") == 0) std::cout << "S\n";
             else if (strcmp(*argv, "--reverse-sorted") == 0 || strcmp(*argv, "-rs") == 0) std::cout << "RS\n";
             else if (strcmp(*argv, "--by-length") == 0 || strcmp(*argv, "-l") == 0) std::cout << "L\n";
             else if (strcmp(*argv, "--anagrams") == 0 || strcmp(*argv, "-a") == 0) std::cout << "A\n";
             else if (strcmp(*argv, "--output") == 0 || strcmp(*argv, "-o") == 0) std::cout << "O\n";
             else if (strcmp(*argv, "--palindromes") == 0 || strcmp(*argv, "-p") == 0) std::cout << "P\n";
             else if (strcmp(*argv, "--input") == 0 || strcmp(*argv, "-fi") == 0) std::cout << "FI\n";
                 //            else if (strcmp(*argv, "--file") == 0 || strcmp(*argv, "-f") == 0) std::cout << "C\n"; // my own
             else std::cout << "B";
         }
     }
 */
    return 0;
}



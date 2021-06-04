#include <vector>
#include <set>
#include <algorithm>

#include "../../include/wrappers/arguments_wrapper.h"
#include "../../tools/include/collectors/words_collector.h"
#include "../../tools/include/collectors/path_collector.h"

wrappers::arguments_wrapper *wrappers::arguments_wrapper::_instance = nullptr;

namespace wrappers {

    arguments_wrapper *arguments_wrapper::getInstance() {
        assert(arguments_wrapper::_instance);
        return arguments_wrapper::_instance;
    }

    void arguments_wrapper::createInstance(std::vector<std::string> &s) {
        assert(!_instance);
        _instance = new arguments_wrapper(s);

    }

    arguments_wrapper::arguments_wrapper(std::vector<std::string>
                                         &s) : _args_vector(std::move(s)) {}

    arguments_wrapper::~arguments_wrapper() = default;

    std::vector<std::string> &arguments_wrapper::args_vector() {
        return _args_vector;
    }

    void arguments_wrapper::set_args_vector(const std::vector<std::string> &argsVector) {
        _args_vector = argsVector;
    }

    /**
     * Function converts flag aliases to flags, and removes duplicate flags, the repeated calling of which does not
     * affect the operation of the program
     * @param flag_properties - map that stores flags, flag aliases, and error text
     */
    void arguments_wrapper::adjust_arguments(flag_properties_map &flag_properties) {
        for (auto const&[key, val] : flag_properties)
            std::replace(_args_vector.begin(), _args_vector.end(), std::string(val.first), std::string(key));

        auto predicate = [](const std::string &a, const std::string &b) {
            return (a == b && (a == "-f" || a == "-l"));
        };
        _args_vector.erase(std::unique(_args_vector.begin(), _args_vector.end(), predicate), _args_vector.end());
    }

    /**
     * Searches the list of _arguments with which the program was started and returns the pointer to position of the last
     * file path specified before the given position
     * @param position - position of the flag against which argument list should be searched
     * @return pointer to position of the last file path before the position of the flag
     */
    std::vector<std::string>::reverse_iterator arguments_wrapper::reverse_find_path(int position) {
        auto &&predicate = [](std::string &s) { return (s[0] != '-' && (&s)[-1] == "-f"); };
        return reverse_find(position, predicate);
    }

    /**
     * Searches the list of _arguments with which the program was started and returns the pointer to position the first flag
     * specified after given position
     * @param position -  position of the flag against which argument list should be searched
     * @return pointer to position of the next flag specified after given position
     */
    std::vector<std::string>::iterator arguments_wrapper::next_flag_position(int position) {
        auto &&predicate = [](std::string &s) { return (s[0] == '-'); };
        return forward_find(position + 1, predicate);
    }

    /**
     * Searches the list of _arguments with which the program was started and returns the pointer to position of the last
     * flag specified after given position
     * @param position - position of the flag against which argument list should be searched
     * @return pointer to position of the last flag specified before given position
     */
    std::vector<std::string>::reverse_iterator arguments_wrapper::previous_flag_position(int position) {
        auto &&predicate = [](std::string &s) { return (s[0] == '-'); };
        auto it = reverse_find(position, predicate);
        return it;
    }

    /**
     * Return vector of words used as input by the -a and -p flags
     * @param position - position of the flag against which argument list should be searched
     * @return vector of words taken from the _arguments
     */
    std::set<std::string> arguments_wrapper::get_words(int position) {
        auto passed = collectors::words_collector();
        passed.collect(position);
        return passed.getCollectedWords();
    }

    /**
     * Return paths to files the paths of the files to be merged with the input file
     * @param position - position of the flag against which argument list should be searched
     * @return vector of paths taken from the _arguments
     */
    std::vector<std::string> arguments_wrapper::get_paths(int position) {
        auto passed = collectors::path_collector();
        passed.collect(_args_vector, position);
        return passed.getCollectedWords();
    }
}
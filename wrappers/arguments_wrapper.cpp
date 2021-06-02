#include <iostream>
#include <vector>
#include <algorithm>

#include "arguments_wrapper.h"

using flag_properties_map = std::map<std::string, std::pair<std::string, std::string>>;


namespace wrappers {


    std::vector<std::string>::reverse_iterator arguments_wrapper::reverse_find_path(int index) {
        auto &&predicate = [](std::string &s) { return (s[0] != '-' && (&s)[-1] == "-f"); };
        return reverse_find(index, predicate);
    }

    std::vector<std::string> &arguments_wrapper::getArguments() {
        return args_vector;
    }

    std::set<std::string> arguments_wrapper::return_words_arguments(int position) {
        auto passed = collectors::passed_words_collector();
        passed.collect(args_vector, position);
        return passed.getCollectedWords();
    }

    std::vector<std::string> arguments_wrapper::return_paths(int position) {
        auto it = get_next_flag_position(position);

        auto passed = collectors::path_collector();
        passed.collect(args_vector, position, it);
        return passed.getCollectedWords();
    }


    std::vector<std::string>::iterator arguments_wrapper::get_next_flag_position(int position) {
        auto &&predicate = [](std::string &s) { return (s[0] == '-'); };
        auto it = forward_find(position + 1, predicate);
        return it;
    }

    void arguments_wrapper::adjust_arguments(flag_properties_map &flag_properties) {
        for (auto const&[key, val] : flag_properties)
            std::replace(args_vector.begin(), args_vector.end(), std::string(val.first), std::string(key));

        auto predicate = [](const std::string &a, const std::string &b) {
            return (a == b && (a == "-f" || a == "-l"));
        };
        args_vector.erase(
                std::unique(args_vector.begin(), args_vector.end(), predicate),
                args_vector.end());
    }

    std::vector<std::string>::reverse_iterator arguments_wrapper::get_previous_flag_position(int position) {
        auto &&predicate = [](std::string &s) { return (s[0] == '-'); };
        auto it = reverse_find(position, predicate);
        return it;
    }

    arguments_wrapper::arguments_wrapper(std::vector<std::string>
                                         &s) : args_vector(std::move(s)) {}
}
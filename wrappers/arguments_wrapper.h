#ifndef PJATEXT2_ARGUMENTS_WRAPPER_H
#define PJATEXT2_ARGUMENTS_WRAPPER_H

#include <iostream>
#include <utility>
#include <vector>
#include <algorithm>
#include <map>

#include "../collectors/passed_words_collector.h"
#include "../collectors/path_collector.h"

using flag_properties_map = std::map<std::string, std::pair<std::string, std::string>>;


namespace wrappers {
    struct arguments_wrapper {
    private:
        std::vector<std::string> args_vector;

    public:

        explicit arguments_wrapper(std::vector<std::string> &s);

        template<typename F>
        inline auto reverse_find(int index, F &&predicate);

        template<typename F>
        inline auto forward_find(int index, F &&predicate);

        std::vector<std::string>::reverse_iterator reverse_find_path(int index);

        std::set<std::string> return_words_arguments(int position);

        std::vector<std::string> return_paths(int position);

        std::vector<std::string> &getArguments();

        std::vector<std::string>::iterator get_next_flag_position(int position);

        std::vector<std::string>::reverse_iterator get_previous_flag_position(int position);

        auto &operator[](std::size_t index) { return args_vector[index]; };

        ~arguments_wrapper() = default;

        void adjust_arguments(flag_properties_map &flag_properties);

    };
}

#include "arguments_wrapper.tpp"

#endif

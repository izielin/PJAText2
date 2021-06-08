#ifndef PJATEXT2_ARGUMENTS_WRAPPER_H
#define PJATEXT2_ARGUMENTS_WRAPPER_H

#include <iostream>
#include <utility>
#include <vector>
#include <algorithm>
#include <map>
#include <set>
#include <cassert>
#include "../../global/global_aliases.h"

namespace wrappers {

    struct arguments_wrapper {
    private:
        std::vector<std::string> _args_vector;
        static arguments_wrapper *_instance;

        explicit arguments_wrapper(std::vector<std::string> &s);

    public:

        arguments_wrapper(const arguments_wrapper &) = delete;

        arguments_wrapper &operator=(const arguments_wrapper &) = delete;

        static arguments_wrapper *getInstance();

        static void createInstance(std::vector<std::string> &s);

        std::vector<std::string> &args_vector();

        void set_args_vector(const std::vector<std::string> &argsVector);

        ~arguments_wrapper();

        template<typename F>
        inline auto reverse_find(iterator position, F &predicate);

        template<typename F>
        inline auto forward_find(int index, F &predicate);

        void adjust_arguments(flag_properties_map &flag_properties);

        reverse_iterator reverse_find_path(iterator position);

        iterator next_flag_position(int position);

        reverse_iterator previous_flag_position(iterator position);

        std::set<std::string> get_words(int position);

        std::vector<std::string> get_paths(int position);

        auto &operator[](std::size_t index) { return _args_vector[index]; };
    };
}

#include "arguments_wrapper.tpp"

#endif

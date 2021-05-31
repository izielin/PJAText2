//
// Created by mmich on 31.05.2021.
//

#ifndef PJATEXT2_CONTAINER_H
#define PJATEXT2_CONTAINER_H

#include <iostream>
#include <utility>
#include <vector>
#include <algorithm>

#include "../collectors/passed_words_collector.h"

namespace containers {
    struct argument_container {
        std::vector<std::string> args_vector;

    public:

        explicit argument_container(std::vector<std::string> &s) : args_vector(std::move(s)) {}

        template<typename F>
        inline auto reverse_find(int index, F &&predicate);

        template<typename F>
        inline auto forward_find(int index, F &&predicate);

        std::vector<std::string>::reverse_iterator find_next_path(int index);

        std::set<std::string> return_words_arguments(int position);

        std::vector<std::string> &getArguments();

        auto &operator[](std::size_t index) { return args_vector[index]; }

        ~argument_container() = default;

    };
}

#include "container.tpp"

#endif //PJATEXT2_CONTAINER_H

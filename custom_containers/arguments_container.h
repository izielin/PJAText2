//
// Created by mmich on 31.05.2021.
//

#ifndef PJATEXT2_ARGUMENTS_CONTAINER_H
#define PJATEXT2_ARGUMENTS_CONTAINER_H

#include <iostream>
#include <utility>
#include <vector>
#include <algorithm>

#include "../collectors/passed_words_collector.h"

class arguments_container {
private:
    std::vector<std::string> arguments;

public:

    explicit arguments_container(std::vector<std::string> &s) : arguments(std::move(s)) {}

    template<typename F>
    auto reverse_find(int index, F &&predicate) {
        return std::find_if(arguments.rbegin() + (arguments.size() - index), arguments.rend(), predicate);
    }

    template<typename F>
    auto forward_find(int index, F &&predicate) {
        return std::find_if(arguments.begin() + index, arguments.end(), predicate);
    }

    auto find_next_path(int index) {
        auto &&predicate = [](std::string &s) { return (s[0] != '-' && (&s)[-1] == "-f"); };
        return reverse_find(index, predicate);
    }

    std::vector<std::string> &getArguments() {
        return arguments;
    }


    auto &operator[](std::size_t index) { return arguments[index]; }

    auto return_words_arguments(int position) {
        auto passed = collectors::passed_words_collector();
        passed.collect(arguments, position);
        return passed.getCollectedWords();
    }

    ~arguments_container() = default;


};


#endif //PJATEXT2_ARGUMENTS_CONTAINER_H

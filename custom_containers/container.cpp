//
// Created by mmich on 31.05.2021.
//

#include <iostream>
#include <vector>

#include "container.h"

namespace containers {
    std::vector<std::string>::reverse_iterator argument_container::find_next_path(int index) {
        auto &&predicate = [](std::string &s) { return (s[0] != '-' && (&s)[-1] == "-f"); };
        return reverse_find(index, predicate);
    }

    std::vector<std::string> &argument_container::getArguments() {
        return args_vector;
    }

    std::set<std::string> argument_container::return_words_arguments(int position) {
        auto passed = collectors::passed_words_collector();
        passed.collect(args_vector, position);
        return passed.getCollectedWords();
    }
}
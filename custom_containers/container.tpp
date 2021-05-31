//
// Created by mmich on 31.05.2021.
//

#ifndef PJATEXT2_CONTAINER_TPP
#define PJATEXT2_CONTAINER_TPP


#include <iostream>
#include <utility>
#include <vector>
#include <algorithm>

#include "../collectors/passed_words_collector.h"

namespace containers {

    template<typename F>
    auto argument_container::reverse_find(int index, F &&predicate) {
        return std::find_if(args_vector.rbegin() + (args_vector.size() - index), args_vector.rend(), predicate);
    }

    template<typename F>
    auto argument_container::forward_find(int index, F &&predicate) {
        return std::find_if(args_vector.begin() + index, args_vector.end(), predicate);
    }
}
#endif // PJATEXT2_CONTAINER_TPP
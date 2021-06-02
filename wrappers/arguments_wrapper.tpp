#ifndef PJATEXT2_ARGUMENTS_WRAPPER_TPP
#define PJATEXT2_ARGUMENTS_WRAPPER_TPP


#include <iostream>
#include <utility>
#include <vector>
#include <algorithm>

#include "../collectors/passed_words_collector.h"
#include "arguments_wrapper.h"


namespace wrappers {

    template<typename F>
    auto arguments_wrapper::reverse_find(int index, F &&predicate) {
        return std::find_if(args_vector.rbegin() + (args_vector.size() - index), args_vector.rend(), predicate);
    }

    template<typename F>
    auto arguments_wrapper::forward_find(int index, F &&predicate) {
        return std::find_if(args_vector.begin() + index, args_vector.end(), predicate);
    }


}
#endif
#ifndef PJATEXT2_ARGUMENTS_WRAPPER_TPP
#define PJATEXT2_ARGUMENTS_WRAPPER_TPP


#include <iostream>
#include <utility>
#include <vector>
#include <algorithm>

#include "arguments_wrapper.h"

namespace wrappers {

    template<typename F>
    auto arguments_wrapper::reverse_find(iterator position, F &predicate) {
        auto index = std::distance(std::make_reverse_iterator(position), _args_vector.rbegin());
        auto iter = _args_vector.rbegin() + index;
        return std::find_if(iter, _args_vector.rend(), predicate);
    }

    template<typename F>
    auto arguments_wrapper::forward_find(int index, F &predicate) {
        return std::find_if(_args_vector.begin() + index, _args_vector.end(), predicate);
    }

}
#endif
#ifndef PJATEXT2_INPUT_DATA_WRAPPER_TPP
#define PJATEXT2_INPUT_DATA_WRAPPER_TPP

#include <iostream>
#include <utility>
#include <vector>
#include <algorithm>

template<typename F>
void wrappers::input_data_wrapper::sort(F predicate) {
    std::sort(_data_vector.begin(), _data_vector.end(), predicate);
}

#endif
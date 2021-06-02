#ifndef PJATEXT2_INPUT_DATA_WRAPPER_TPP
#define PJATEXT2_INPUT_DATA_WRAPPER_TPP

#include <iostream>
#include <utility>
#include <vector>
#include <algorithm>

#include "../collectors/passed_words_collector.h"


template<typename F>
void wrappers::input_data_wrapper::sort(F predicate) {
    std::sort(data_vector.begin(), data_vector.end(), predicate);
}

#endif
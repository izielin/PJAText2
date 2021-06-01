//
// Created by mmich on 31.05.2021.
//

#ifndef PJATEXT2_ENHANCED_VECTOR_TPP
#define PJATEXT2_ENHANCED_VECTOR_TPP


#include <iostream>
#include <utility>
#include <vector>
#include <algorithm>

#include "../collectors/passed_words_collector.h"

namespace containers {

    template<typename F>
    void containers::enhanced_vector::sort(F predicate) {
        std::sort(data_vector.begin(), data_vector.end(), predicate);
    }
}
#endif // PJATEXT2_ENHANCED_VECTOR_TPP
#ifndef PJATEXT2_UTILITY_FUNCTIONS_TPP
#define PJATEXT2_UTILITY_FUNCTIONS_TPP

namespace utility {

    /**
     * A generic function used to print the contents of containers such as set or vector
     * @tparam TT - container type
     * @tparam Args - type of elements in container
     * @param container - container to print
     * @param output_stream - stream the result should be returned to
     */
    template<template<typename, typename...> class TT, typename Args>
    void print_container(const TT<Args> &container, stream_helper &output_stream) {
        for (auto it = container.begin(); it != container.end(); ++it) {
            if (it != container.begin())
                output_stream << ", ";
            output_stream << *it;
        }
        output_stream << '\n';
    }
}

#endif
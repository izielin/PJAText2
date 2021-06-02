#ifndef PJATEXT2_UTILITY_FUNCTIONS_TPP
#define PJATEXT2_UTILITY_FUNCTIONS_TPP


namespace utility {

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
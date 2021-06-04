#ifndef PJATEXT2_STREAM_HELPER_H
#define PJATEXT2_STREAM_HELPER_H

#include <iostream>

/**
 * Class defining the stream to which the results of the program operation are to be returned
 */
class stream_helper {
    std::ostream &_ostream;
public:
    explicit stream_helper(std::ostream &out) : _ostream(out) {}

    ~stream_helper() = default;

    template<typename T>
    friend stream_helper &operator<<(stream_helper &h, T const &t);
};

#include "stream_helper.tpp"

#endif

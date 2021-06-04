#ifndef PJATEXT2_STREAM_HELPER_TPP
#define PJATEXT2_STREAM_HELPER_TPP

#include "stream_helper.h"

template<typename T>
stream_helper &operator<<(stream_helper &h, T const &t) {
    h._ostream << t;
    return h;
}

#endif

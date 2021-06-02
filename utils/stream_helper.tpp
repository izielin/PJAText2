#ifndef PJATEXT2_STREAM_HELPER_TPP
#define PJATEXT2_STREAM_HELPER_TPP

template<typename T>
stream_helper &operator<<(stream_helper &h, T const &t) {
    h.ostream << t;
    return h;
}


#endif

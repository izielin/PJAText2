//
// Created by mmich on 30.05.2021.
//

#ifndef PJATEXT2_STREAM_HELPER_H
#define PJATEXT2_STREAM_HELPER_H

#include <iostream>


class stream_helper {
    std::ostream &ostream;
public:
    explicit stream_helper(std::ostream &out1) : ostream(out1) {}

    ~stream_helper() = default;

    template<typename T>
    friend stream_helper &operator<<(stream_helper &h, T const &t) {
        h.ostream << t;
        return h;
    }
};


#endif //PJATEXT2_STREAM_HELPER_H

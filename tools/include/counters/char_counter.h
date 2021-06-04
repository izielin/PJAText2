#ifndef PJATEXT2_CHAR_COUNTER_H
#define PJATEXT2_CHAR_COUNTER_H

#include <iostream>
#include <vector>

/**
 * A structure that provide functionality to count chars from given vector.
 */
namespace counters {
    class char_counter {
    private:
        int _amount = 0;
    public:
        char_counter();

        void count(std::vector<std::string> &vector_searched);

        int amount() const;

        ~char_counter();
    };
}

#endif

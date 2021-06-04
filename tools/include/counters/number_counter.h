#ifndef PJATEXT2_NUMBER_COUNTER_H
#define PJATEXT2_NUMBER_COUNTER_H

#include <iostream>
#include <vector>

/**
 * A structure that provide functionality to count numbers from given vector.
 */
namespace counters {
    class number_counter {
    private:
        int _amount = 0;
    public:
        number_counter();

        void count(std::vector<std::string> &vector_searched);

        int amount() const;

        ~number_counter();
    };
}

#endif

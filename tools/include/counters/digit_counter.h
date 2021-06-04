#ifndef PJATEXT2_DIGIT_COUNTER_H
#define PJATEXT2_DIGIT_COUNTER_H

#include <iostream>
#include <vector>

/**
 * A structure that provide functionality to count digits from given vector.
 */
namespace counters {
    class digit_counter {
    private:
        int _amount = 0;
    public:
        digit_counter();

        void count(std::vector<std::string> &vector_searched);

        int amount() const;

        ~digit_counter();
    };
}


#endif

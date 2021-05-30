//
// Created by mmich on 28.05.2021.
//

#ifndef PJATEXT2_COUNTERS_H
#define PJATEXT2_COUNTERS_H

#include <iostream>


namespace counters {
    class number_counter {
    private:
        int amount = 0;
    public:
        number_counter() = default;

        void count();

        int get_amount() const;

        ~number_counter() = default;
    };

    class digit_counter {
    private:
        int amount = 0;
    public:
        digit_counter() = default;

        void count();

        int get_amount() const;

        ~digit_counter() = default;
    };

    class char_counter {
    private:
        int amount = 0;
    public:
        char_counter() = default;

        void count(const std::string &path);

        int get_amount() const;

        ~char_counter() = default;
    };
}

#endif //PJATEXT2_COUNTERS_H

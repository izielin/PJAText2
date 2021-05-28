//
// Created by mmich on 28.05.2021.
//

#ifndef PJATEXT2_COUNTERS_H
#define PJATEXT2_COUNTERS_H

#include <iostream>


namespace counting_methods {


    class counter {
    public:
        counter() = default;

        ~counter() = default;

        virtual void count() = 0;
    };

    class number_counter : public counter {
    private:
        int amount = 0;
    public:
        number_counter() = default;

        void count() override;

        int get_amount() const;

        ~number_counter() = default;
    };

    class digit_counter : public counter {
    private:
        int amount = 0;
    public:
        digit_counter() = default;

        void count() override;

        int get_amount() const;

        ~digit_counter() = default;
    };

}

#endif //PJATEXT2_COUNTERS_H

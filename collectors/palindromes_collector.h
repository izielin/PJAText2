#ifndef PJATEXT2_PALINDROMES_COLLECTOR_H
#define PJATEXT2_PALINDROMES_COLLECTOR_H

#include <iostream>
#include <set>
#include "../wrappers/arguments_wrapper.h"

namespace collectors {
    class palindromes_collector {
    private:
        std::set<std::string> palindromes;
    public:
        palindromes_collector() = default;

        void collect(std::vector<std::string> &input, wrappers::arguments_wrapper &container, int position);

        const std::set<std::string> &getPalindromes() const;

        ~palindromes_collector() = default;
    };
}

#endif

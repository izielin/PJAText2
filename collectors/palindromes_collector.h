//
// Created by mmich on 29.05.2021.
//

#ifndef PJATEXT2_PALINDROMES_COLLECTOR_H
#define PJATEXT2_PALINDROMES_COLLECTOR_H

#include <iostream>
#include <set>

namespace collectors {
    class palindromes_collector {
    private:
        std::set<std::string> palindromes;
    public:
        palindromes_collector() = default;

        void collect(std::vector<std::string> &vector_searched, int position);

        const std::set<std::string> &getPalindromes() const;

        ~palindromes_collector() = default;
    };


}

#endif //PJATEXT2_PALINDROMES_COLLECTOR_H

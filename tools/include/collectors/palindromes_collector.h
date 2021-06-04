#ifndef PJATEXT2_PALINDROMES_COLLECTOR_H
#define PJATEXT2_PALINDROMES_COLLECTOR_H

#include <iostream>
#include <set>
#include "../../../include/wrappers/arguments_wrapper.h"

/**
 * A structure that provide functionality to collect palindromes from the input file.
 */
namespace collectors {
    class palindromes_collector {
    private:
        std::set<std::string> _palindromes;
    public:
        palindromes_collector();

        void collect(std::vector<std::string> &vector_searched, int position);

        const std::set<std::string> &palindromes() const;

        ~palindromes_collector();
    };
}

#endif

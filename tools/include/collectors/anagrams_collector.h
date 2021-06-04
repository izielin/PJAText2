#ifndef PJATEXT2_ANAGRAMS_COLLECTOR_H
#define PJATEXT2_ANAGRAMS_COLLECTOR_H

#include <iostream>
#include <map>
#include <set>
#include <vector>
#include "../../../include/wrappers/arguments_wrapper.h"

/**
 * A structure that provide functionality to collect anagrams from the input file.
 */
namespace collectors {
    class anagrams_collector {
    private:
        std::map<std::string, std::set<std::string>> _anagrams;
    public:
        anagrams_collector();

        void collect(std::vector<std::string> &vector_searched, int position);

        const std::map<std::string, std::set<std::string>> &anagrams() const;

        ~anagrams_collector();
    };
}

#endif

//
// Created by mmich on 29.05.2021.
//

#ifndef PJATEXT2_ANAGRAMS_COLLECTOR_H
#define PJATEXT2_ANAGRAMS_COLLECTOR_H

#include <iostream>
#include <map>
#include <set>
#include <vector>
#include "../custom_containers/argument_container.h"

namespace collectors {
    class anagrams_collector {
    private:
        std::map<std::string, std::set<std::string>> anagrams;
    public:
        anagrams_collector() = default;

        void collect(std::vector<std::string> &input_vector, containers::argument_container &container, int position);

        const std::map<std::string, std::set<std::string>> &getAnagrams() const;

        ~anagrams_collector() = default;
    };
}

#endif //PJATEXT2_ANAGRAMS_COLLECTOR_H

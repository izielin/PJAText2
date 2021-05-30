//
// Created by mmich on 29.05.2021.
//

#ifndef PJATEXT2_PASSED_WORDS_COLLECTOR_H
#define PJATEXT2_PASSED_WORDS_COLLECTOR_H

#include <iostream>
#include <set>
#include <vector>


namespace collectors {
    class passed_words_collector {
    private:

        std::set<std::string> arguments;
    public:

        passed_words_collector() = default;


        void collect(std::vector<std::string> &vector_searched, int position);

        const std::set<std::string> &getArguments() const;

        ~passed_words_collector() = default;
    };


}

#endif //PJATEXT2_PASSED_WORDS_COLLECTOR_H

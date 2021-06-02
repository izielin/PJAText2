#ifndef PJATEXT2_PASSED_WORDS_COLLECTOR_H
#define PJATEXT2_PASSED_WORDS_COLLECTOR_H

#include <iostream>
#include <set>
#include <vector>


namespace collectors {
    class passed_words_collector {
    private:

        std::set<std::string> collected_words;
    public:

        passed_words_collector() = default;

        void collect(std::vector<std::string> &vector_searched, int position);

        std::set<std::string> &getCollectedWords();

        ~passed_words_collector() = default;
    };


}

#endif

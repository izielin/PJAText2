#ifndef PJATEXT2_WORDS_COLLECTOR_H
#define PJATEXT2_WORDS_COLLECTOR_H

#include <iostream>
#include <set>
#include <vector>

/**
 * A structure that provide functionality to collects words from arguments with which the program was called.
 */
namespace collectors {
    class words_collector {
    private:
        std::set<std::string> collected_words;
    public:
        words_collector();

        void collect(int position);

        std::set<std::string> &getCollectedWords();

        ~words_collector();
    };
}

#endif

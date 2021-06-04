#include <iostream>

#include "../../include/collectors/words_collector.h"
#include "../../../include/wrappers/arguments_wrapper.h"

collectors::words_collector::words_collector() = default;

collectors::words_collector::~words_collector() = default;

std::set<std::string> &collectors::words_collector::getCollectedWords() {
    return collected_words;
}

/**
 * Collect words from argument of the program.
 * @param vector_searched - vector to search
 * @param position - position of the flag against which argument list should be searched
 */
void collectors::words_collector::collect(int position) {
    auto vector_searched = wrappers::arguments_wrapper::getInstance()->args_vector();
    for (auto iterator = vector_searched.begin() + position;
         iterator != vector_searched.end(); collected_words.insert(*iterator++));
}



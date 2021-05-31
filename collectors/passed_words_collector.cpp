//
// Created by mmich on 29.05.2021.
//

#include <iostream>

#include "passed_words_collector.h"

void collectors::passed_words_collector::collect(std::vector<std::string> &vector_searched, int position) {
    for (auto iterator = vector_searched.begin() + position;
         iterator != vector_searched.end(); collected_words.insert(*iterator++));
}

std::set<std::string> &collectors::passed_words_collector::getCollectedWords() {
    return collected_words;
}

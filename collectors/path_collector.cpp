#include <iostream>

#include "path_collector.h"

void collectors::path_collector::collect(std::vector<std::string> &vector_searched, int position,
                                         std::vector<std::string>::iterator it) {
    for (auto iterator = vector_searched.begin() + position;
         iterator != it; collected_paths.emplace_back(*iterator++));

}

std::vector<std::string> &collectors::path_collector::getCollectedWords() {
    return collected_paths;
}


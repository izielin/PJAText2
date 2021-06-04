#include <iostream>

#include "../../include/collectors/path_collector.h"
#include "../../../include/wrappers/arguments_wrapper.h"

collectors::path_collector::path_collector() = default;

collectors::path_collector::~path_collector() = default;

std::vector<std::string> &collectors::path_collector::getCollectedWords() {
    return collected_paths;
}

/**
 * Collect words from argument of the program.
 * @param vector_searched - vector to search
 * @param position - position of the flag against which argument list should be searched
 */
void collectors::path_collector::collect(std::vector<std::string> &vector_searched, int position) {
    auto iterator = wrappers::arguments_wrapper::getInstance()->next_flag_position(position);
    for (auto iter = vector_searched.begin() + position; iter != iterator;
         collected_paths.emplace_back(*iter++)) {
    };

}
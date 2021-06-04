#include <iostream>
#include <algorithm>

#include "../../include/collectors/words_collector.h"
#include "../../include/collectors/anagrams_collector.h"

collectors::anagrams_collector::anagrams_collector() = default;

collectors::anagrams_collector::~anagrams_collector() = default;

const std::map<std::string, std::set<std::string>> &collectors::anagrams_collector::anagrams() const {
    return _anagrams;
}

/**
 * Check whether two strings are anagram of each other.
 * @param word_1 - the word whose anagrams are being searched for
 * @param word_2 - word to check if is an anagram of the first one
 * @return true if words are anagram of each other, false if not
 */
auto are_anagram(const std::string &word_1, const std::string &word_2) {
    int count[256] = {0};

    // If strings have different length return false
    if (word_1.length() != word_2.length())
        return false;

    for (int i = 0; word_1[i] && word_2[i]; i++) {
        count[tolower(word_1[i])]++;
        count[tolower(word_2[i])]--;
    }

    // check if there is any non-zero value in array
    for (int i : count)
        if (i) return false;
    return true;
}

/**
 * Collect anagrams from the given vector matching those given in the argument of the program.
 * @param vector_searched - vector to search
 * @param position - position of the flag against which argument list should be searched
 */
void collectors::anagrams_collector::collect(std::vector<std::string> &vector_searched, int position) {
    auto filtered_words = wrappers::arguments_wrapper::getInstance()->get_words(position);
    std::set<std::string> matching_words;

    if (filtered_words.empty()) {
        std::cout << "No anagrams to found were given" << '\n';
        return;
    }

    for (auto &word_1 : filtered_words) {
        for (auto &word_2 : vector_searched) {
            if (are_anagram(word_1.c_str(), word_2.c_str())) {
                std::transform(word_2.begin(), word_2.end(), word_2.begin(),
                               [](unsigned char c) { return std::tolower(c); });
                matching_words.insert(word_2);
            }
        }

        _anagrams.insert(std::make_pair(word_1, matching_words));
        matching_words.clear();
    }
}



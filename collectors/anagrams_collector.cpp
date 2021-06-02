#include <iostream>
#include <algorithm>

#include "passed_words_collector.h"
#include "anagrams_collector.h"

#define NO_OF_CHARS 256

const std::map<std::string, std::set<std::string>> &collectors::anagrams_collector::getAnagrams() const {
    return anagrams;
}

/**
 * \brief Function check whether two strings are anagram of each other
 * @param word_1
 * @param word_2
 * @return
 */
auto are_anagram(const std::string &word_1, const std::string &word_2) {
    /* The function iterates over the given words. Increase the value in the count array
     * for the characters in str1 and decrease it for the characters in str2.
     * If the numbers are all 0, then these two strings are anagrams of each other.
    */

    int count[NO_OF_CHARS] = {0};

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

void collectors::anagrams_collector::collect(std::vector<std::string> &input_vector,
                                             wrappers::arguments_wrapper &container, int position) {
    std::set<std::string> matching_words;

    auto passed = container.return_words_arguments(position);
    for (auto &&word : passed) {
        for (auto &&item : input_vector) {
            if (are_anagram(word.c_str(), item.c_str())) {
                std::transform(item.begin(), item.end(), item.begin(),
                               [](unsigned char c) { return std::tolower(c); });
                matching_words.insert(item);
            }
        }

        anagrams.insert(std::make_pair(word, matching_words));
        matching_words.clear();
    }
}

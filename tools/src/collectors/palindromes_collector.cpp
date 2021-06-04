#include <iostream>
#include <algorithm>
#include <map>

#include "../../include/collectors/palindromes_collector.h"

collectors::palindromes_collector::palindromes_collector() = default;

collectors::palindromes_collector::~palindromes_collector() = default;

const std::set<std::string> &collectors::palindromes_collector::palindromes() const {
    return _palindromes;
}

/**
 * Check if given word is palindrome.
 * @param word - word to check
 * @return true if word is palindrome, false if not
 */
bool is_palindrome(const std::string &word) {
    int l = 0, h = word.length() - 1;
    while (h > l)
        if (tolower(word[l++]) != tolower(word[h--])) return false;
    return true;
}

/**
 * Collect palindromes from the given vector matching those given in the argument of the program.
 * @param vector_searched - vector to search
 * @param position - position of the flag against which argument list should be searched
 */
void collectors::palindromes_collector::collect(std::vector<std::string> &vector_searched, int position) {
    auto filtered_words = wrappers::arguments_wrapper::getInstance()->get_words(position);

    if (filtered_words.empty()) {
        std::cout << "No palindromes to found were given" << '\n';
        return;
    }

    auto predicate = [&](const std::string &word) {
        return (is_palindrome(word) &&
                std::find(vector_searched.begin(), vector_searched.end(), word) != vector_searched.end());
    };

    std::copy_if(filtered_words.begin(), filtered_words.end(),
                 std::inserter(_palindromes, _palindromes.end()), predicate);
}
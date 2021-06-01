//
// Created by mmich on 29.05.2021.
//

#include <iostream>
#include <algorithm>
#include <map>

#include "palindromes_collector.h"

const std::set<std::string> &collectors::palindromes_collector::getPalindromes() const {
    return palindromes;
}

bool is_palindrome(const std::string &word) {
    int l = 0, h = word.length() - 1;
    while (h > l)
        if (tolower(word[l++]) != tolower(word[h--])) return false;
    return true;
}


void
collectors::palindromes_collector::collect(std::vector<std::string> &input,
                                           containers::argument_container &container,
                                           int position) {
    auto filtered_words = container.return_words_arguments(position);

    auto predicate = [&](const std::string &word) {
        return (is_palindrome(word) &&
                std::find(input.begin(), input.end(), word) != input.end());
    };

    std::copy_if(filtered_words.begin(), filtered_words.end(),
                 std::inserter(palindromes, palindromes.end()), predicate);
}
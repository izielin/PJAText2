//
// Created by mmich on 29.05.2021.
//

#include <iostream>
#include <algorithm>
#include <map>

#include "palindromes_collector.h"
#include "passed_words_collector.h"

#include "../global.h"

const std::set<std::string> &collectors::palindromes_collector::getPalindromes() const {
    return palindromes;
}

bool is_palindrome(const std::string &word) {
    int l = 0, h = word.length() - 1;
    while (h > l)
        if (word[l++] != word[h--]) return false;
    return true;
}

bool predicate(const std::string &word) {
    return (is_palindrome(word) &&
            std::find(input_vector.begin(), input_vector.end(), word) != input_vector.end());
}

void collectors::palindromes_collector::collect(std::vector<std::string> &vector_searched, int position) {

    auto passed = passed_words_collector();
    passed.collect(vector_searched, position);

    std::copy_if(passed.getArguments().begin(), passed.getArguments().end(),
                 std::inserter(palindromes, palindromes.end()), predicate);


}
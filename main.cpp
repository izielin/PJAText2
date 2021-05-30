//
// Created by mmich on 25.05.2021.
//

#include <iostream>
#include <algorithm>
#include <vector>
#include "utils/check_arguments_correctness.h"


int main(int argc, char *argv[]) {

    auto arguments = std::vector<std::string>(argv + 1, argv + argc);

    check::check_arguments_correctness(arguments);

    return 0;
}



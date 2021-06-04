#include <algorithm>
#include <vector>
#include "include/utils/check_arguments_correctness.h"

int main(int argc, char *argv[]) {

    auto vec = std::vector<std::string>(argv + 1, argv + argc);
    wrappers::arguments_wrapper::createInstance(vec);

    check_arguments_correctness();

    return 0;
}

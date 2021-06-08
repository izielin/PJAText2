#include <algorithm>
#include <vector>
#include "include/utils/check_arguments_correctness.h"
#include "global/global_variables.h"

int main(int argc, char *argv[]) {

    auto vec = std::vector<std::string>(argv + 1, argv + argc);
    wrappers::arguments_wrapper::createInstance(vec);

    arguments = wrappers::arguments_wrapper::getInstance();
    arguments_vector = arguments->args_vector();

    check_arguments_correctness();

    return 0;
}

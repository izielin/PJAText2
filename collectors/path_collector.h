#ifndef PJATEXT2_PATH_COLLECTOR_H
#define PJATEXT2_PATH_COLLECTOR_H

#include <iostream>
#include <vector>

namespace collectors {
    class path_collector {
    private:

        std::vector<std::string> collected_paths;
    public:

        path_collector() = default;


        void collect(std::vector<std::string> &vector_searched, int position, std::vector<std::string>::iterator it);

        std::vector<std::string> &getCollectedWords();

        ~path_collector() = default;
    };


}

#endif

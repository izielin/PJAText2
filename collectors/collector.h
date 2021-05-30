//
// Created by mmich on 29.05.2021.
//

#ifndef PJATEXT2_COLLECTOR_H
#define PJATEXT2_COLLECTOR_H

namespace collectors {
    class collector {

    public:

        collector() = default;

        virtual void collect(std::vector <std::string> &vector_searched, int position) = 0;

        ~collector() = default;
    };


}

#endif //PJATEXT2_COLLECTOR_H

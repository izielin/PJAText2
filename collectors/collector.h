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

#endif

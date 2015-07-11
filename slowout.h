#ifndef SLOWOUT_H
#define SLOWOUT_H

#include <sstream>

using std::stringstream;
namespace zoel{

    class SlowOut : public stringstream{
    public:
        SlowOut();
        void print();
        static unsigned int timeStep;
    };
}
#endif

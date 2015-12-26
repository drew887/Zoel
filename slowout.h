#ifndef SLOWOUT_H
#define SLOWOUT_H

#include <ostream>
#include <sstream>

using std::stringstream;
using std::ostream;
namespace zoel{

    class SlowOut : public stringstream{
    public:
        void print();
        friend ostream& operator<<(ostream& out, const SlowOut * slow);
        static unsigned int timeStep;
    };
}
#endif

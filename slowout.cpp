#include "slowout.h"
#include <string>
#include <cstdio>

#ifdef _WIN32
#include <windows.h>
#define safesleep(seconds) Sleep(seconds)
#endif
#ifndef _WIN32
#include <unistd.h>
#define safesleep(seconds) usleep(seconds*1000)
#endif

using std::string;
using namespace zoel;

unsigned int SlowOut::timeStep = 10;

void SlowOut::print(){
    string output = str(); //this is stringstream::str()
    for(unsigned int letter = 0; letter < output.size(); letter++){
        putchar(output[letter]);
        fflush(stdout);
        safesleep(timeStep);
    }
    str("");
}

ostream& operator<<(ostream& out, const SlowOut * slow){
    string output = slow->str();
    for(unsigned int letter = 0; letter < output.size(); letter++){
        out << output[letter];
        out.flush();
        safesleep(slow->timeStep);
    }
    return out;
}

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

unsigned int SlowOut::timeStep = 20;

SlowOut::SlowOut(){

}

void SlowOut::print(){
    string output = str();
    for(unsigned int letter = 0; letter < output.size(); letter++){
        putchar(output[letter]);
        fflush(stdout);
        safesleep(timeStep);
    }
    str("");
}


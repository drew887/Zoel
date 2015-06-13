#ifndef SOUNDENG_H
#define SOUNDENG_H

#include "hoot.h"
#include <vector>
#include <string>

//a singleton for handling sound
class soundEng{
	soundEng();
	~soundEng();
	Hoot2d hoot;
	std::vector<Source *> sources;
	unsigned int currentSong;
public:
	static soundEng & getInstance();

	void play(unsigned int song);
	void addSong(std::string path);
    soundEng(soundEng const&);
    void operator=(soundEng const&);
};

#endif

#include "soundEng.h"

soundEng::soundEng(){
	currentSong = 0;
}
soundEng::~soundEng(){
	for (unsigned int ctr = 0; ctr < sources.size(); ctr++){
		delete sources[ctr];
	}
}

soundEng & soundEng::getInstance(){
	static soundEng instance;
	return instance;
}

void soundEng::play(unsigned int song){
	if (song < sources.size()){
		sources[currentSong]->stop();
		sources[song]->play();
		currentSong = song;
	}
}

void soundEng::addSong(std::string path){
	sources.push_back(new Source(path.c_str()));
}
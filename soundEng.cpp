/*
* soundEng.cpp
* This file is part of Zoel
*
* Copyright (C) 2013 - 2015 - Andrew Mcdonald
*
* Zoel is free software; you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation; either version 3 of the License, or
* (at your option) any later version.
*
* Zoel is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with Zoel; if not, write to the Free Software
* Foundation, Inc., 51 Franklin St, Fifth Floor,
* Boston, MA  02110-1301  USA
*/

#include "soundEng.h"

SoundEng::SoundEng(){
    currentSong = 0;
}
SoundEng::~SoundEng(){
    for(unsigned int ctr = 0; ctr < sources.size(); ctr++){
        delete sources[ctr];
    }
}

SoundEng & SoundEng::getInstance(){
    static SoundEng instance;
    return instance;
}

void SoundEng::play(unsigned int song){
    if(song < sources.size()){
        sources[currentSong]->stop();
        sources[song]->play();
        currentSong = song;
    }
}

void SoundEng::addSong(std::string path){
    sources.push_back(new Source(path.c_str()));
}

unsigned int SoundEng::getNumSongs(){
    return sources.size();
}

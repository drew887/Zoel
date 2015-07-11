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

soundEng::soundEng(){
    currentSong = 0;
}
soundEng::~soundEng(){
    for(unsigned int ctr = 0; ctr < sources.size(); ctr++){
        delete sources[ctr];
    }
}

soundEng & soundEng::getInstance(){
    static soundEng instance;
    return instance;
}

void soundEng::play(unsigned int song){
    if(song < sources.size()){
        sources[currentSong]->stop();
        sources[song]->play();
        currentSong = song;
    }
}

void soundEng::addSong(std::string path){
    sources.push_back(new Source(path.c_str()));
}

unsigned int soundEng::getNumSongs(){
    return sources.size();
}
/*
* soundEng.h
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
	unsigned int getNumSongs();
};

#endif

/*
 * room.h
 * This file is part of Zoel
 *
 * Copyright (C) 2013 - Andrew Mcdonald
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
#include "stdafx.h"
#pragma once
#ifndef ROOM_MAX
#define ROOM_MAX 4
#endif 

enum room_dir{NONE=0,NORTH=1,EAST,SOUTH,WEST=4};
//struct
void movecheck(unsigned char te);
void batcheck(unsigned char te);
#pragma pack(1)
class room{
public:
	room(const char * descr);
	room(void);
	void rexit(room * rexit);
	virtual ~room(void);
	bool addper(entity * person);
	bool attach(room * ar, room_dir direc);
        bool attach(room * ar, room_dir direc,bool t);
	virtual room* start(player * playera);
	virtual void addwep(Weapon weps){}
	room * getdir(room_dir dir);
	char desc[1024];
protected:
	void movecheck(unsigned char te);
	void batcheck(unsigned char te);
	entity * enimies[ROOM_MAX];
	//player * One;
	struct attacher{
	room * attached[4];
	room_dir at_dir[4];
	};
	attacher attached;
	unsigned int attcount;
	unsigned int percount;
};
#pragma pack()

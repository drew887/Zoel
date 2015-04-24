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


#ifndef ROOM_H
#define ROOM_H
#include "entity.h"
#include "player.h"
#ifndef ROOM_MAX
#define ROOM_MAX 4
#endif 
enum ROOM_ERR{ ALL_CON_USED, CON_ALREADY_USED, ROOM_FULL, DEAD_PLAYER, ROOM_DONE, NO_ROOMS_ATTACHED, MAIN_STREET, SUBWAY, LOADED_RES };
enum room_dir{ NONE = 0, NORTH = 1, EAST, SOUTH, WEST = 4 };
void movecheck(unsigned char te);
void batcheck(unsigned char te);
#pragma pack(1)
class room{
public:
	room(const char * descr, unsigned int romnum);
	room(void);
	void rexit(room * rexit);
	virtual ~room(void);
	bool addper(entity * person);
	bool attach(room * ar, room_dir direc);
	bool attach(room * ar, room_dir direc, bool t);
	virtual room* start(player * playera);
	virtual void addwep(Weapon weps){}
	room * getdir(room_dir dir);
	char desc[1024];
	virtual void setpic(bool set){}
protected:
	unsigned int mynum;
	virtual void parse(player * playera);
	room * next;
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
#endif
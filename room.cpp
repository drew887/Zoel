/*
 * room.cpp
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
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>
#include "room.h"
#include "player.h"

room::room(const char * descr){
	percount = 0;
	attcount = 0;
	for (unsigned int i = 0; i < 4; i++){
		attached.at_dir[i] = NONE;
		attached.attached[i] = NULL;
	}
	strcpy(desc, descr);
}

room* room::start(player * playera){
	static const char roomstar[] = "\t*****************\n%s\n\t*****************\n";
	printf(roomstar, desc);
	if (attcount == 0){ throw NO_ROOMS_ATTACHED; }
	return this->next;
}
bool room::addper(entity * person){
	bool success = true;
	if (percount < ROOM_MAX){
		enimies[percount] = person;
		percount++;
	}
	else{ success = false; }
	return success;
}
inline room_dir swit(room_dir tw){
	switch (tw){
	case NORTH:
		return SOUTH;
		break;
	case SOUTH:
		return NORTH;
		break;
	case WEST:
		return EAST;
		break;
	case EAST:
		return WEST;
		break;
	}
	return NONE;
}

bool room::attach(room * ar, room_dir direct, bool connectBack){
	if (attcount >= 4){
		throw ALL_CON_USED;
		return false;
	}
	for (unsigned char i = 0; i < 4; i++){
		if (attached.at_dir[i] == direct){
			printf("CON %i\n", i); throw CON_ALREADY_USED; return false;
		}
	}
	attached.attached[attcount] = ar;
	attached.at_dir[attcount] = direct;
	attcount++;
	if (connectBack)
	{
		ar->attach(this, swit(direct));
	}
	return true;
}
room::~room(void){
	for (char i = 0; i < 4; i++){
		attached.attached[i] = NULL;
		attached.at_dir[i] = NONE;
	}
}

room * room::getRoomAtDir(room_dir dir){
	room * temp = NULL;
	for (unsigned char i = 0; i < attcount; i++){
		if (attached.at_dir[i] == dir){
			temp = attached.attached[i];
			break;
		}
	}
	return temp;
}

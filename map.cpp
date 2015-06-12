/*
* map.cpp
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
#include "map.h"
#include <stdio.h>
#include <string.h>
#include <iostream>

using namespace std;
using std::string;
Map::Map(string desc) :description(desc){

}


Map::~Map(){
	for (unsigned int ctr = 0; ctr < rooms.size(); ctr++){
		delete rooms[ctr];
	}
}

void Map::connectRoom(unsigned int one, unsigned int two, room_dir dir, bool twoWay){
	if ((one != two) && (one < rooms.size()) && (two < rooms.size())){
		rooms[one]->attach(rooms[two], dir, twoWay);
	}
}

struct room_t{
	string desc;
	vector<int> connections;
	vector<char>directions;
};

room_dir determineDir(char dir){
	room_dir direction = NONE;
	switch (dir){
	case 'N':
		direction = NORTH;
		break;
	case 'E':
		direction = EAST;
		break;
	case 'S':
		direction = SOUTH;
		break;
	case 'W':
		direction = WEST;
		break;
	}
	return direction;
}

bool Map::load(std::string filename){
	bool loaded = false;
	vector<room_t> room_types;
	FILE * pp = fopen(filename.c_str(), "rb");
	if (pp){
		char check[5] = {};
		fread(check, 4, 1, pp);
		if (!strncmp(check, "ZMAP", 4)){
			unsigned int numRooms = 0;
			fread(&numRooms, sizeof(int), 1, pp);
			for (unsigned int loop = 0; loop < numRooms; loop++){
				fread(check, 4, 1, pp);
				if (!strncmp(check, "ROOM", 4)){
					room_t room;
					unsigned int descLength = 1;
					fread(&descLength, sizeof(int), 1, pp);
					char * tDesc = new char[descLength + 1];
					tDesc[descLength] = 0;
					fread(tDesc, descLength, 1, pp);
					room.desc = tDesc;
					delete[] tDesc;
					unsigned int roomCount = 0;
					fread(&roomCount, sizeof(int), 1, pp);
					for (unsigned int ctr = 0; ctr < roomCount; ctr++){
						unsigned int num = 0;
						char dir = 'N';
						fread(&num, sizeof(int), 1, pp);
						fread(&dir, sizeof(char), 1, pp);
						room.connections.push_back(num);
						room.directions.push_back(dir);
					}
					room_types.push_back(room);
					rooms.push_back(new Room(room.desc.c_str()));
				}
				else{
					cout << "ERR READING ROOM" << endl;
				}
			}
			for (unsigned int ctr = 0; ctr < room_types.size(); ctr++){
				for (unsigned int loop = 0; loop < room_types[ctr].connections.size(); loop++){
					connectRoom(ctr, room_types[ctr].connections[loop], determineDir(room_types[ctr].directions[loop]), false);
				}
			}
		}
		else{
			cout << "File is not a valid ZMAP" << endl;
		}
		fclose(pp);
	}
	else{
		cout << "File not found!" << endl;
	}
	return loaded;
}


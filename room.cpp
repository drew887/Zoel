/*
 * room.cpp
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
#include <cstdlib>
#include <iostream>
#include <cmath>
#include <cstring>

#include "room.h"
#include "player.h"

using namespace std;

vector<string> Room::tokens = { "north", "east", "south", "west", "quit", "help", "stats", "save", "load", "look", "attack" };


Room::Room(const char * descr) :description(descr){
	percount = 0;
	attcount = 0;
	next = NULL;
	for (unsigned int i = 0; i < 4; i++){
		at_dir[i] = NONE;
		attached[i] = NULL;
	}
}

inline room_dir directionSwap(room_dir tw){
	switch (tw){
	case NORTH:
		tw = SOUTH;
		break;
	case SOUTH:
		tw = NORTH;
		break;
	case WEST:
		tw = EAST;
		break;
	case EAST:
		tw = WEST;
		break;
	default:
		tw = NONE;
	}
	return tw;
}

Room * Room::start(Player * playera){
	cout << description << endl;
	if (attcount == 0){
		//throw NO_ROOMS_ATTACHED;
		return NULL;
	}
	idleLoop(playera);
	return this->next;
}

bool Room::addper(Entity * person){
	bool success = true;
	if (percount < ROOM_MAX){
		enimies[percount] = person;
		percount++;
	}
	else{
		success = false;
	}
	return success;
}

bool Room::attach(Room * ar, room_dir direct, bool connectBack){
	if (attcount >= 4){
		return false;
	}
	attached[attcount] = ar;
	at_dir[attcount] = direct;
	attcount++;
	if (connectBack)
	{
		ar->attach(this, directionSwap(direct));
	}
	return true;
}

Room::~Room(void){
	for (int i = 0; i < 4; i++){
		attached[i] = NULL;
		at_dir[i] = NONE;
	}
}

Room * Room::getRoomAtDir(room_dir dir){
	Room * temp = NULL;
	for (unsigned char i = 0; i < attcount; i++){
		if (at_dir[i] == dir){
			temp = attached[i];
			break;
		}
	}
	return temp;
}

void Room::idleLoop(Player *play){
	bool loop = true;
	while (loop){
		cout << endl << "> ";
		string msg;
		getline(cin, msg);
		cout << endl;
		vector<string> words;
		char * mesg = new char[msg.size() + 1];
		strcpy(mesg, msg.c_str());
		for (unsigned int character = 0; character < msg.size(); character++){
			mesg[character] = tolower(mesg[character]);
		}
		char * tok = strtok(mesg, " ");
		while (tok != NULL){
			if (strcmp(tok, "the")){
				words.push_back(tok);
			}
			tok = strtok(NULL, " ");
		}
		delete mesg;

		unsigned int token;
		for (token = 0; token < tokens.size(); token++){
			if (words[0] == tokens[token]){
				break;
			}
		}
		switch (token){
		case 0:
		case 1:
		case 2:
		case 3:
			next = getRoomAtDir((room_dir)token);
			if (next != NULL){
				loop = false;
			}
			else{
				cout << "you can't go that way" << endl;
			}
			break;
		case 4:
			loop = false;
			next = NULL;
			break;
		case 5:
			cout << "The commands are:" << endl;
			for (unsigned int ctr = 0; ctr < tokens.size(); ctr++){
				cout << "  " << tokens[ctr] << endl;
			}
			break;
		case 6:
			play->stats();
			break;
		case 7:
			play->save();
			break;
		case 8:
			cout << "please enter a name to load: "; { //cordon off this block to stop cross label initialization errors
				std::string name;
				getline(cin, name);
				if (play->load(name.c_str())){
					//figure out a good way to handle loading
				}
			}
			break;
		case 9: //look
			cout << description << endl;
			break;
		case 10: //attack
			if (words.size() < 2){
				cout << "Attack what?: " << endl;
			}
			else{
				cout << "Attacking the " << words[1] << endl;
			}
			break;
		default:
			cout << "I don't know " << words[0] << endl;
		}
	}
}

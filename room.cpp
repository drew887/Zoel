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
#include <iostream>
#include <math.h>
#include "room.h"
#include "player.h"

using namespace std;

string room::tokens[] = {"north","east","south","west","quit","help","stats"};
unsigned int room::numTokens = 7;

room::room(const char * descr):description(descr){
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

room * room::start(player * playera){
    cout << "*****\n" << description << "\n*****" <<endl;
    if (attcount == 0){
		throw NO_ROOMS_ATTACHED;
	}
    idleLoop(playera);
	return this->next;
}
bool room::addper(entity * person){
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

bool room::attach(room * ar, room_dir direct, bool connectBack){
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
room::~room(void){
    for (int i = 0; i < 4; i++){
		attached[i] = NULL;
		at_dir[i] = NONE;
	}
}

room * room::getRoomAtDir(room_dir dir){
	room * temp = NULL;
	for (unsigned char i = 0; i < attcount; i++){
		if (at_dir[i] == dir){
			temp = attached[i];
			break;
		}
	}
	return temp;
}

void room::idleLoop(player *play){
    bool loop = true;
    while(loop){
        cout << "Enter a Command: " << endl;
        string msg;
        getline(cin,msg);
        unsigned int token;
        for(token = 0; token < numTokens; token++){
            if(msg == tokens[token]){
                break;
            }
        }
        if(token < numTokens){
            if(token < 4){//the directions
                next = getRoomAtDir((room_dir)token);
                if(next != NULL){
                    loop = false;
                }else{
                    cout << "you can't go that way" << endl;
                }
            }
            if(token == 4){ //quit
                loop = false;
                next = NULL;
            }
            if(token == 5){ //help
                cout << "The commands are:" << endl;
                for(unsigned int ctr = 0; ctr < numTokens; ctr++){
                    cout << "  " << tokens[ctr] << endl;
                }
            }
            if(token == 6){ //stats
                play->stats();

            }
        }else{
            cout << "I don't know " << msg << endl;
        }

    }
}

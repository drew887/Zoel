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
	next = NULL;
	for (unsigned int i = 0; i < 4; i++){
		at_dir[i] = NONE;
		attached[i] = NULL;
	}
	strcpy(desc, descr);
}

inline room_dir swit(room_dir tw){
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
void cleanStdin(int count = 80){
    char in = getc(stdin);
    int ctr = 0;
    while(in != EOF && in != '\n' && ctr < count){
        in = getc(stdin);
        ctr++;
    }
}

room * room::start(player * playera){
	static const char roomstar[] = "\t*****************\n%s\n\t*****************\n";
	printf(roomstar, desc);
	if (attcount == 0){
		throw NO_ROOMS_ATTACHED;
	}
    parse();
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
	for (unsigned char i = 0; i < 4; i++){
		if (at_dir[i] == direct){
			printf("CON %i\n", i); 
			return false;
		}
	}
	attached[attcount] = ar;
	at_dir[attcount] = direct;
	attcount++;
	if (connectBack)
	{
		ar->attach(this, swit(direct));
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

void room::parse(){
    bool loop = true;
    while(loop){
        printf("Enter a Command: ");
        cleanStdin();
        char msg[80] = {};
        scanf("%79[^\n]",msg);
        switch(msg[0]){
        case 'n':
            if(!strncmp("north",msg,5)){
                this->next = this->getRoomAtDir(NORTH);
                if(this->next == NULL){
                    printf("Can't go that way\n");
                }else{
                    loop = false;
                }
            }
            break;
        case 'e':
            if(!strncmp("east",msg,4)){
                this->next = this->getRoomAtDir(EAST);
                if(this->next == NULL){
                    printf("Can't go that way\n");
                }else{
                    loop = false;
                }
            }
            break;
        case 's':
            if(!strncmp("south",msg,5)){
                this->next = this->getRoomAtDir(SOUTH);
                if(this->next == NULL){
                    printf("Can't go that way\n");
                }else{
                    loop = false;
                }
            }
            break;
        case 'w':
            if(!strncmp("west",msg,4)){
                this->next = this->getRoomAtDir(WEST);
                if(this->next == NULL){
                    printf("Can't go that way\n");
                }else{
                    loop = false;
                }
            }
            break;
        case 'q':
            this->next = NULL;
            loop = false;
            break;
        default:
            printf("I don't know %s \n",msg);
        }
    }
}

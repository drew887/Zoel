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
#include "stdafx.h"
#include "room.h"
#include <math.h>
extern char bigmap[200];
room::room(const char * descr,unsigned int romnum){
	mynum = romnum;
	percount = 0;
	attcount = 0;
	for(unsigned int i = 0;i<4;i++){
	attached.at_dir[i] = NONE;
	attached.attached[i] = NULL;
	}
	strcpy(desc,descr);
}
room::room(void){
	percount = 0;
	attcount = 0;
	desc[0] = 'a';
	desc[1] = '\0';
}

room* room::start(player * playera){
	const char roomstar[] = "\t*****************\n%s\n\t*****************\n";
	char dontknow[] = "I don't know \"%s\"\n";
	printf(roomstar,desc);
	if(attcount == 0){throw NO_ROOMS_ATTACHED; return NULL;}
//	One = playera;
	this->next = NULL;
	bool vic = true;
	bool infi = true;
	char rancheck = 0;
	unsigned int numcheck =0;
	char te[200];
   if(percount>0){
	while (vic){
	   if(enimies[numcheck]->isalive){
		printf("******\nAn enemy %s is attacking!!\n******\n",enimies[numcheck]->classname);
		while(infi){
			printf("Enter a command!\n***a = attack r = run q = quit***\n");
			scanf("%100[^\n]",te);
			clearin();
			switch(te[0]){
			case 'a':
				if( (strlen(te) ==1) || (!strcmp("attack",te)) ){
				if(enimies[numcheck]->defend(playera)){
					infi = false;
				}else{enimies[numcheck]->attack(playera);}
			}else{printf(dontknow,te);}
			break;
			case 'r':
			
		if( (strlen(te) ==1) || (!strcmp("run",te)) ){
			rancheck = floor((rand() % 2) + 1);
			if(rancheck == 2){
			    mprintf("You managed to run away and make it back here safely\n");
                                infi = false;
                                vic = false;
			    }else{
				printf("You failed and the %s gets you off guard!\n",enimies[numcheck]->classname);
				enimies[numcheck]->attack(playera);
			    }
		}else{printf(dontknow,te);}
			break;
			case 'q':
				exit(0);
			break;
			default:
				printf(dontknow,te);
			}
                }//end while infi
	   }else{}
		numcheck++;
		infi = true;
		if(numcheck == percount){vic=false;}
        }//end while vic
    }//end if percount
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
	parse(playera);
	return this->next;
}
bool room::addper(entity * person){
	if(percount < ROOM_MAX){
	enimies[percount] = person;
	percount++;
	}else{throw ROOM_FULL;return false;}
	return true;
}
bool room::attach(room * ar, room_dir direct){
	if(attcount >= 4){
		throw ALL_CON_USED;
		return false;
	}
	for(unsigned char i = 0;i<4;i++){
		if(attached.at_dir[i] == direct){
                        printf("CON %i\n",attached.at_dir[i]);throw CON_ALREADY_USED; return false;
		}
	}
        attached.attached[attcount] = ar;
	attached.at_dir[attcount] = direct;
	attcount++;
        return true;
}
room_dir swit(room_dir tw){
    switch(tw){
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
}

bool room::attach(room * ar, room_dir direct,bool t){
        if(attcount >= 4){
                throw ALL_CON_USED;
                return false;
        }
        for(unsigned char i = 0;i<4;i++){
                if(attached.at_dir[i] == direct){
                        printf("CON %i\n",i);throw CON_ALREADY_USED; return false;
                }
        }
        attached.attached[attcount] = ar;
        attached.at_dir[attcount] = direct;
        attcount++;
        ar->attach(this,swit(direct));
        return true;
}
room::~room(void){
    for(char i = 0; i<4;i++){
    attached.attached[i] = NULL;
    attached.at_dir[i] = NONE;
	}
}

room * room::getdir(room_dir dir){
	room * temp = NULL;
	for(unsigned char i = 0; i<attcount;i++){
		if(attached.at_dir[i] == dir){
			temp = attached.attached[i];
			break;
		}
	}
	return temp;
}
void room::parse(player * playera){
	char te[200];
	bool chose =true;
const char cantgo[] = "You can't go that way\n";
const char dontknow[] = "I don't know \"%s\"\n";
	while(chose){
		mprintf("Enter a command!\n***compass directions to move q to quit, help for help***\n");
		scanf("%100[^\n]",te);
		clearin();
		switch(te[0]){
		case 'n': 
		if((strlen(te) ==1) || (!strncmp("north",te,5)) ){
			this->next = getdir(NORTH);
			if(this->next == NULL){printf(cantgo);}else{
				chose =false;
			}
		}else{printf(dontknow,te);}
		break;
        case 'l':
        if(!strcmp("look",te)){
		printf("\t*****************\n%s\n\t*****************\n",desc);
                break;
		}else if(!strcmp("load",te)){
			char loaded[9];
		mprintf("Enter the name of a previous character\n");
		scanf("%8s",loaded);
		clearin();
		playera->load(loaded);
		//return this;
		break;
		}
		else{printf(dontknow,te);}
			break;
		case 'e': 
		if( (strlen(te)==1) || (!strcmp("east",te)) ){
			this->next = getdir(EAST);
			if(this->next ==NULL){printf(cantgo);}else{
				chose =false;
			}
		}else{printf(dontknow,te);}
		break;
		case 's': 
			if( (strlen(te)==1) || (!strcmp("south",te)) ){
			this->next = getdir(SOUTH);
			if(this->next ==NULL){printf(cantgo);}else{
				chose =false;
			}
		}else if(!strcmp("save",te)){
			playera->save();
			break;
		}else if(!strcmp("stats",te)){
			playera->stats();
			break;
		}
		else{printf(dontknow,te);}
		break;
		case 'w': 
			if( (strlen(te)==1) || (!strcmp("west",te)) ){
			this->next = getdir(WEST);
			if(this->next ==NULL){printf(cantgo);}else{
				chose =false;
			}
			break;
		}else{printf(dontknow,te);}
		break;
		case 'q':
			exit(0);
		break;
		case 'm':
		if(!strcmp("map",te)){
		playera->showmap(bigmap,mynum);

		}else{printf(dontknow,te);}
		break;
		case 'h':
		if(!strcmp("help",te)){
		mprintf("n/north\tgo north\ne/east\tgo east\ns/south\tgo south\nw/west\tgo west\nq\tquit\nlook\tlook around\nsave\tsave the game\nload\tload a game\nstats\t show yer stats\n");
		}else{printf(dontknow,te);}
		break;
		default:
			printf(dontknow,te);
		}
	}	
}

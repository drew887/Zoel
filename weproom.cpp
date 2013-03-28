/*
 * weproom.cpp
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
#include <math.h>
weproom::weproom(const char * descr):room(descr){

}
void weproom::addwep(Weapon weps){
wepa = weps;
}
room * weproom::start(player *playera){
printf("\t*****************\n%s\n\t*****************\n",desc);
    if(attcount == 0){throw NO_ROOMS_ATTACHED; return NULL;}
    room * next = NULL;
    bool vic = true;
    bool infi = true;
    bool chose = true;
    char rancheck = 0;
    unsigned int numcheck =0;
    unsigned char te = 0;
if(percount>0){
   printf("Oh no, %d enemie[s]!\n",percount);
    while (vic){
       if(enimies[numcheck]->isalive){
	    printf("******\nAn enemy %s is attacking!!\n******\n",enimies[numcheck]->classname);
	    while(infi){
		    printf("Enter a command!\n***a = attack r = run q = quit***\n");
		    scanf("%c",&te);
		    clearin();
		    switch(te){
		    case 'a':
			    if(enimies[numcheck]->defend(playera)){
				    infi = false;
			    }else{enimies[numcheck]->attack(playera);}
		    break;
		    case 'r':
		    rancheck = floor((rand() % 20) + 1);
		    if((rancheck % 2)==0){
			mprintf("You managed to run away and make it back here safely\n");
			    infi = false;
			    vic = false;
			}else{
			    printf("You failed and the %s gets you off guard!\n",enimies[numcheck]->classname);
			    enimies[numcheck]->attack(playera);
			}
		    break;
		    case 'q':
			    exit(0);
		    break;
		    default:
			    printf("Unknown action?\n");
		    }
	    }//end while infi
       }else{mprintf("This ones dead!\n");}
	    numcheck++;
	    infi = true;
	    if(numcheck == percount){vic=false;}
    }//end while vic
}//end if percount
mprintf("You found a weapon!\nIt's a ");
playera->giveWep(wepa);
playera->tellwep();
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
    while(chose){
	    mprintf("Enter a command!\n***compass directions to move q to quit, h for help***\n");
	    scanf("%c",&te);
	    clearin();
	    switch(te){
	    case 'n':
		    next = getdir(NORTH);
		    if(next ==NULL){printf("You can't go that way\n");}else{
			    chose =false;
		    }
	    break;
	    case 'S':
	    playera->save();
	    break;
	    case 'L':
	    char loaded[9];
	    mprintf("Enter the name of a previous character\n");
	    scanf("%8s",loaded);
	    clearin();
	    playera->load(loaded);
	    return this;
	    break;
	    case 'l':
	    printf("\t*****************\n%s\n\t*****************\n",desc);
	    break;
	    case 'e':
		    next = getdir(EAST);
		    if(next ==NULL){printf("You can't go that way\n");}else{
			    chose =false;
		    }
	    break;
	    case 's':
		    next = getdir(SOUTH);
		    if(next ==NULL){printf("You can't go that way\n");}else{
			    chose =false;
		    }
	    break;
	    case 'w':
		    next = getdir(WEST);
		    if(next ==NULL){printf("You can't go that way\n");}else{
			    chose =false;
		    }
	    break;
	    case 'q':
		    exit(0);
	    break;
	    case 'h':
	    mprintf("n\tgo north\ne\tgo east\ns\tgo south\nw\tgo west\nq\tquit\nl\tlook around\nS\tsave\nL\tload\n");
	    break;
	    default:
		    mprintf("I dont know that command\n");
	    }
    }
    return next;
}//end weproom::start

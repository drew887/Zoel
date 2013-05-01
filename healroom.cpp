/*
 * healroom.cpp
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
extern char bigmap[200];
healroom::healroom(const char * descr,unsigned int romnum):room(descr,romnum){

}
room * healroom::start(player *playera){
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
		    rancheck = floor((rand() % 2) + 1);
		    if(rancheck == 2){
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
mprintf("\t**********\nYou've entered a healing light within the room and you\nsuddenly feel healed and restored! :D\n\t***********\n");
playera->heal();
playera->stats();
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
    parse(playera);
    return this->next;
}//end healroom::start


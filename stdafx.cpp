/*
 * stdafx.cpp
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
// stdafx.cpp : source file that includes just the standard includes
// Zoel.pch will be the pre-compiled header
// stdafx.obj will contain the pre-compiled type information
#include "stdafx.h"
#include <string.h>
extern entity * tes[6];
extern room * rooms[10];
extern exitroom * exitr;
extern exitroom * conecter;
extern ROOM_ERR dep;
extern player * Me;
// TODO: reference any additional headers you need in STDAFX.H
// and not in this file
void mprintf(const char * de){
unsigned int ns = strlen(de);
    for(unsigned int i =0;i<ns;i++){
	//printf("%c",de[i]);
	putchar(de[i]);
	fflush(stdout);
#ifndef _WIN32
	//usleep(20000);
#endif
#ifdef _WIN32
	safesleep(17);
#endif
    }
//printf("\n");
}
extern char bigmap[200];
extern char mapnum[10];
extern unsigned char curmapnum;
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
void mainstreet(){
curmapnum = 1;
char mainmap[] = "   \t   \t   \t   \t %c\n   \t | \t   \t   \t |\n   \t %c-\t---\t-%c-\t-%c\n   \t | \t   \t | \t\n   \t %c-\t-%c-\t-%c\n   \t   \t | \n %c-\t-%c-\t-%c\n";
char mainnum[] = {'9','6','7','8','4','3','5','2','0','1'};
strcpy(mapnum,mainnum);
strcpy(bigmap,mainmap);
    FILE * pp = fopen("two","rb");
    char * tempdesc;
    if(!pp){printf("Corrupt or improper story file for the subway.\nPlease ask Andrew about this or redownload the story files\n");exit(0xDEAD);}
    unsigned int count = 0;
    dep = ROOM_DONE;
    for(int i = 0; i<6; i++){if(i==5){tes[i]=new Joel();}else{tes[i] = new zombie();}}
    conecter = new exitroom(SUBWAY);
    exitr = new exitroom(ROOM_DONE);
    for(int i = 0; i<10;i++){
	fread(&count,4,1,pp);
	if(feof(pp)){printf("Corrupt or improper story file for the mainstreet. %d\nPlease ask Andrew about this or redownload the story files\n",i);exit(0xDEAD);}
	tempdesc = new char[count+1];
	fread(tempdesc,count,1,pp);
	tempdesc[count] = '\0';
	if(feof(pp)){printf("Corrupt or improper story file for the mainstreet. %d\nPlease ask Andrew about this or redownload the story files\n",i);exit(0xDEAD);}
	if(i==4){
	rooms[i] = new healroom(tempdesc,i);
	}else if(i==2){
	Weapon Jorels;
	strcpy(Jorels.name,"JoelSlay");
	Jorels.att = 6;
	Jorels.spd = 4;
	rooms[i] = new weproom(tempdesc,i);
	if(strncmp("JoelSlay",Me->wep.name,8)==0){
	rooms[i]->setpic(true);
	}
	rooms[i]->addwep(Jorels);
	}else{
	rooms[i] = new room(tempdesc,i);
	}
	delete[] tempdesc;
	tempdesc = NULL;
	//printf("%s\n",tempdesc);
    }
    fclose(pp);
    //rooms0
	 rooms[0]->attach(rooms[1],NORTH,true);
	 rooms[0]->attach(rooms[2],SOUTH,true);
	 rooms[0]->attach(conecter,EAST);
	 //rooms1
	 rooms[1]->attach(rooms[3],WEST,true);
	 rooms[1]->addper(tes[3]);
	 //roms2
	 rooms[2]->addper(tes[0]);
	 //rooms3
	 rooms[3]->attach(rooms[4],SOUTH,true);
	 rooms[3]->attach(rooms[5],NORTH,true);
	 //rooms4
	 rooms[4]->attach(rooms[6],WEST,true);
	 //roms5
	 rooms[5]->attach(rooms[7],WEST,true);
	 rooms[5]->addper(tes[1]);
	 //roms6
	 rooms[6]->attach(exitr,WEST);
	 rooms[6]->attach(rooms[7],NORTH,true);
	 rooms[6]->addper(tes[2]);
	 //rooms7
	 rooms[7]->attach(rooms[8],NORTH,true);
	 rooms[7]->addper(tes[4]);
	 //roms8
	 rooms[8]->attach(rooms[9],WEST,true);
	 //rooms9
	 rooms[9]->addper(tes[5]);
}




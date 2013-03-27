// stdafx.cpp : source file that includes just the standard includes
// Zoel.pch will be the pre-compiled header
// stdafx.obj will contain the pre-compiled type information

#include "stdafx.h"
extern zombie * tes[6];
extern room * rooms[10];
extern exitroom * exitr;
extern exitroom * conecter;
extern ROOM_ERR dep;
// TODO: reference any additional headers you need in STDAFX.H
// and not in this file
void mainstreet(){
    FILE * pp = fopen("two","rb");
    char * tempdesc;
    if(!pp){printf("Corrupt or improper story file for the subway.\nPlease ask Andrew about this or redownload the story files\n");exit(0xDEAD);}
    unsigned int count = 0;
    dep = ROOM_DONE;
    for(int i = 0; i<6; i++){tes[i] = new zombie();}
    conecter = new exitroom(SUBWAY);
    exitr = new exitroom(ROOM_DONE);
    for(int i = 0; i<10;i++){
	fread(&count,4,1,pp);
	if(feof(pp)){printf("Corrupt or improper story file for the mainstreet. %d\nPlease ask Andrew about this or redownload the story files\n",i);exit(0xDEAD);}
	tempdesc = new char[count+1];
	fread(tempdesc,count,1,pp);
	tempdesc[count] = '\0';
	if(feof(pp)){printf("Corrupt or improper story file for the mainstreet. %d\nPlease ask Andrew about this or redownload the story files\n",i);exit(0xDEAD);}
	rooms[i] = new room(tempdesc);
	delete[] tempdesc;
	tempdesc = NULL;
	//printf("%s\n",tempdesc);
    }
    fclose(pp);
    //rooms0
	 rooms[0]->attach(rooms[1],EAST,true);
	 rooms[0]->attach(rooms[2],WEST,true);
	 rooms[0]->attach(conecter,SOUTH);
	 //rooms1
	 rooms[1]->attach(rooms[3],NORTH,true);
	 //rooms3
	 rooms[3]->attach(rooms[4],WEST,true);
	 rooms[3]->attach(rooms[5],EAST,true);
	 //rooms4
	 rooms[4]->attach(rooms[6],NORTH,true);
	 //roms5
	 rooms[5]->attach(rooms[7],NORTH,true);
	 //roms6
	 rooms[6]->attach(exitr,NORTH);
	 rooms[6]->attach(rooms[7],EAST,true);
	 //rooms7
	 rooms[7]->attach(rooms[8],EAST,true);
	 //roms8
	 rooms[8]->attach(rooms[9],NORTH,true);
}




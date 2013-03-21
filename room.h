#include "stdafx.h"
#pragma once
#ifndef ROOM_MAX
#define ROOM_MAX 4
#endif 

enum room_dir{NORTH=1,EAST,SOUTH,WEST=4};
//struct
void movecheck(unsigned char te);
void batcheck(unsigned char te);
#pragma pack(1)
class room{
public:
	room(const char * descr);
	room(void);
	void rexit(room * rexit);
	virtual ~room(void);
	bool addper(entity * person);
	bool attach(room * ar, room_dir direc);
        bool attach(room * ar, room_dir direc,bool t);
	virtual room* start(player * playera);
	room * getdir(room_dir dir);
protected:
	void movecheck(unsigned char te);
	void batcheck(unsigned char te);
	char desc[1024];
	entity * enimies[ROOM_MAX];
	player * One;
	struct attacher{
	room * attached[4];
	room_dir at_dir[4];
	};
	attacher attached;
	unsigned int attcount;
	unsigned int percount;
};
#pragma pack()

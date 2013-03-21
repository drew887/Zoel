// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//
#pragma once
#ifdef _WIN32
#include <windows.h>
#define safesleep Sleep
#endif
#ifndef _WIN32
#include <unistd.h>
#define safesleep usleep
#endif
#include <time.h>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <stdlib.h>
#include <typeinfo>
#include <time.h>
#include "inventory.h"
#include "player.h"
#include "entity.h"
#include "room.h"
#include "zombie.h"
#include "saver.h"
enum ROOM_ERR{ALL_CON_USED,CON_ALREADY_USED,ROOM_FULL,DEAD_PLAYER,ROOM_DONE,NO_ROOMS_ATTACHED,MAIN_STREET,SUBWAY,LOADED_RES};
#include "exitroom.h"
void startup();
    template <typename h,size_t ns>
void mprintf(h(&de)[ns]){
    for(unsigned int i =0;i<ns;i++){
	printf("%c",de[i]);
	fflush(stdout);
#ifndef _WIN32
	safesleep(20000);
#endif
#ifdef _WIN32
	safesleep(20);
#endif
    }
//printf("\n");
}

template <typename f,size_t N>
int ar(f(&test)[N]){printf("an array of with size %d\n",N);return N;}

using namespace std;
void enter(void);
//enum ROOM_ERR{ALL_CON_USED,CON_ALREADY_USED,ROOM_FULL,DEAD_PLAYER,ROOM_DONE,NO_ROOMS_ATTACHED,MAIN_STREET,SUBWAY};
enum RESULT{WIN,LOSE};
inline void clearin(){
	char ch;
	//fflush(stdin);
	while((ch != '\n')&&(ch != EOF)){
	ch = cin.get();
	}
}
void catcher(ROOM_ERR e);

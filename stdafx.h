/*
 * stdafx.h
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
#include "joel.h"
//#include "saver.h"
#include "healroom.h"
#include "weproom.h"
enum ROOM_ERR{ALL_CON_USED,CON_ALREADY_USED,ROOM_FULL,DEAD_PLAYER,ROOM_DONE,NO_ROOMS_ATTACHED,MAIN_STREET,SUBWAY,LOADED_RES};
#include "exitroom.h"

void startup();
    //template <typename h,size_t ns>
//void mprintf(h(&de)[ns]){
void mprintf(const char * de);
template <typename f,size_t N>
int ar(f(&test)[N]){printf("an array of with size %d\n",N);return N;}

using namespace std;
void enter(void);
enum RESULT{WIN,LOSE};
inline void clearin(){
	char ch = 0;
	//fflush(stdin);
	while((ch != '\n')&&(ch != EOF)){
	ch = cin.get();
	}
}
bool catcher(ROOM_ERR e);
void mainstreet();

/*
 * Zoel.cpp
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
// Zoel.cpp
#include "player.h"
#include "room.h"
#include "hoot.h"
#include "map.h"
#include <stdio.h>
#include <string.h>
#include <signal.h>
void enter();
void startup();
bool catcher(ROOM_ERR e);
int main(int argc, char* argv[]){
	atexit(enter);
	map demo("Subway system");
	demo.rooms.push_back(room("Init room"));
	demo.rooms.push_back(room("demo"));
	demo.connectRoom(0, 1, WEST);
	printf("TO DO\n");

	return 0;
}

#include <iostream>
void enter(void){
	std::cout << "\nPress enter to continue...\n";
	std::cin.ignore(1, '\n');
}

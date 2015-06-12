/*
 * Zoel.cpp
 * This file is part of Zoel
 *
 * Copyright (C) 2013 - 2015 - Andrew Mcdonald
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
#include "player.h"
#include "room.h"
#include "hoot.h"
#include "map.h"
#include "exitroom.h"
#include <stdio.h>
#include <string.h>
#include <signal.h>

void enter();

int main() {
	atexit(enter);
	Map test("TEST");
	test.load("test.zmap");
	Map town("TOWN");
	town.load("town.zmap");
	town.rooms.push_back(new Exitroom("TX", &test, 1));
	test.rooms.push_back(new Exitroom("TX", &town, 3));
	town.connectRoom(3, 5, SOUTH, false);
	test.connectRoom(1, 3, NORTH, false);
	Player one;
	Room * currentRoom = test.rooms[0];
	while (currentRoom != NULL){
		currentRoom = currentRoom->start(&one);
	}
	return 0;
}

#include <iostream>
void enter(void) {
	std::cout << "\nPress enter to continue...\n";
	std::cin.ignore(80, '\n');
}

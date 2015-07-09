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
#include "soundEng.h"
#include "zombie.h"
#include <iostream>

void enter();

int main() {
	atexit(enter);
    Map test("TEST");
	test.load("test.zmap");
	Map town("TOWN");
    town.load("town.zmap");
    test.rooms[1]->addper(new Zombie());
    town.rooms.push_back(new Exitroom("TX", &test, 1));
    test.rooms.push_back(new Exitroom("TX", &town, 1));
    test.connectRoom(1, test.rooms.size()-1, NORTH, false);
    town.connectRoom(1, town.rooms.size()-1, SOUTH, false);
    soundEng::getInstance().play(0);
    Player one;
    Room * currentRoom = test.rooms[0];
	while (currentRoom != NULL){
		currentRoom = currentRoom->start(&one);
    }
	return 0;
}

void enter(void) {
	std::cout << "\nPress enter to continue...\n";
	std::cin.ignore(80, '\n');
}

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
#include "player.h"
#include "room.h"
#include "hoot.h"
#include "map.h"
#include "exitroom.h"
#include <stdio.h>
#include <string.h>
#include <signal.h>
void enter();
int main(){
  atexit(enter);
  Map subway("Subway system");
  subway.rooms.push_back(new Room("Init room"));
  subway.rooms.push_back(new Room("demo"));
  subway.rooms.push_back(new Room("TRHEE"));
  subway.connectRoom(1,2,NORTH);
  subway.connectRoom(2,0,WEST,false);
  subway.connectRoom(0, 1, WEST);
  Map city("City");
  city.rooms.push_back(new Room("Downtown"));
  city.rooms.push_back(new Room("Mall"));
  city.connectRoom(0,1,NORTH);
  subway.rooms.push_back(new Exitroom("SX",&city,0));
  city.rooms.push_back(new Exitroom("CX", &subway, 2));
  subway.connectRoom(2,3,EAST);
  city.connectRoom(0,2,WEST);
  Map test("FAC");
  test.load("mega.zmap");
  Player one;
  Room * currentRoom = test.rooms[0];
  while(currentRoom != NULL){
    currentRoom = currentRoom->start(&one);
  }
  return 0;
}

#include <iostream>
void enter(void){
	std::cout << "\nPress enter to continue...\n";
    std::cin.ignore(80, '\n');
}

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

#include "world.h"

int main(){
    World world;
    if(world.load("zoel.ini")){
        soundEng::getInstance().play(0);
        Player one;
        Room * currentRoom = world.maps[0]->rooms[0];
        world.getMapByName("Small town")->rooms[0]->addper(new Zombie());
        while(currentRoom != NULL){
            currentRoom = currentRoom->start(&one);
        }
    }
    std::cout << "\nPress enter to continue...\n";
    std::cin.ignore(80, '\n');
    return 0;
}


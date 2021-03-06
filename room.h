/*
 * room.h
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

#ifndef ROOM_H
#define ROOM_H
#include "entity.h"
#include "player.h"
#include "inventory.h"

#include <vector>
#include <string>
#ifndef ROOM_MAX
#define ROOM_MAX 4
#endif 
enum room_dir{ NORTH = 0, EAST, SOUTH, WEST, NONE = 4 };
using std::string;
using std::vector;

#pragma pack(1)

class Room {
public:
    Room(string Description);
    virtual ~Room(void);
    bool addPerson(Entity * person);
    void addItem(Item * item);
    bool attach(Room * ar, room_dir direc, bool connectBack = false);
    virtual Room * start(Player * play);
    Room * getRoomAtDir(room_dir dir);
    string description;
protected:
    void printDescription();
    void idleLoop(Player * play);
    Room * next;
    vector<Entity *> enemies;
    vector<Item *> items;
    Room * attached[4];
    room_dir at_dir[4];
    unsigned int attcount;
    static vector<string> tokens;
};
#pragma pack()
#endif

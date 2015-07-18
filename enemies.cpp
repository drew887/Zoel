/*
* enemies.cpp
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

#include "enemies.h"

Slime::Slime(){
    classname = "Slime";
    hp = maxhp = (rand() % 6) + 10;
    def = (rand() % 2) + 1;
    att = (rand() % 1) + 1;
    inventory.push_back(new Item("Slime ball"));
}

Thief::Thief(){
    classname = "Thief";
    hp = maxhp = (rand() % 10) + 5;
    def = (rand() % 1) + 3;
    att = (rand() % 2) + 2;
    inventory.push_back(new Item("Lock pick"));
}

Zombie::Zombie(){
    classname = "Zombie";
    hp = maxhp = (rand() % 5) + 8;
    def = (rand() % 2) + 1;
    att = (rand() % 2) + 1;
    inventory.push_back(new Item("Rotten flesh"));
}

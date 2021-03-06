/*
 * entity.h
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
#ifndef ENTITY_H
#define ENTITY_H

#include "inventory.h"
#include <string>
#include <vector>


class Entity {
protected:
    int maxhp;//i think this is all self explanitory
    int hp;
    unsigned int def;
    unsigned int att;
public:
    std::vector<Item *> inventory;
    std::string classname;
    bool isalive;
    Entity();
    virtual ~Entity();
    virtual bool attack(Entity * defender);//this is the method for attacking, just calls defend for the defender normally, truth be told, kinda useless; but i wanted it anyway just to keep things straight.
    virtual bool defend(Entity * attacker);
    virtual void giveItem(Item * item);
    virtual Item * dropItem(std::string item);
    virtual unsigned int getAttack();
    virtual unsigned int getDefence();
    virtual unsigned int getHp();

};
#endif

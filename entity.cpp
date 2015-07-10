/*
 * entity.cpp
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
#include "entity.h"
#include "slowout.h"
#include <iostream>

using namespace std;

Entity::Entity(){
    isalive =true;
}

Entity::~Entity(){
    for(unsigned int ctr =0; ctr < inventory.size();ctr++){
        delete inventory[ctr];
    }
}

bool Entity::attack(Entity * defender){
	return defender->defend(this);
}
bool Entity::defend(Entity * attacker){
    zoel::SlowOut slow;
    int temphp = hp;
    slow  << attacker->classname << " is attacking! ";
	temphp -= (attacker->getAttack() - def);
	if (temphp >= hp){
        slow << "A MASSIVE 0 damage ";
	}
	else{
        slow << "A Whopping " << (hp - temphp) << " damage! ";
		hp = temphp;
	}
	if (hp <= 0){
        slow << classname << " has been defeated!" << endl << endl;
		isalive = false;
        slow.print();
		return true;
	}
    slow << classname << " has " << hp << " remaining!" << endl << endl;
    slow.print();
	return false;
}

unsigned int Entity::getAttack(){
	return att;
}

unsigned int Entity::getDefence(){
	return def;
}

unsigned int Entity::getHp(){
	return hp;
}

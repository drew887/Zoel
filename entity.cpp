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
    int temphp = hp;
    cout << attacker->classname << " is attacking! ";
	temphp -= (attacker->getatt() - def);
	if (temphp >= hp){
        cout << "A MASSIVE 0 damage ";
	}
	else{
        cout << "A Whopping " << (hp - temphp) << " damage! ";
		hp = temphp;
	}
	if (hp <= 0){
        cout << classname << " has been defeated!" << endl;
		isalive = false;
		return true;
	}
    cout << classname << " has " << hp << " remaining!" << endl;
	return false;
}

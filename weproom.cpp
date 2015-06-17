/*
 * weproom.cpp
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

#include "weproom.h"
#include <iostream>

using namespace std;

WeaponRoom::WeaponRoom(const char * descr) :Room(descr){

}
void WeaponRoom::addwep(Weapon * weps){
	weaponList.push_back(weps);
}
Room * WeaponRoom::start(Player *){
	cout << "*****\n" << description << "\n*****" << endl;
	if (attcount == 0){
		throw NO_ROOMS_ATTACHED;
	}
	return this->next;
}

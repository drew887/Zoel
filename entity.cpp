/*
 * entity.cpp
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
#include "entity.h"
#include <stdio.h>

bool entity::attack(entity * defender){
	return defender->defend(this);
}
bool entity::defend(entity * attacker){
	//char classname[8];
	int temphp = hp;
	printf("%s is attacking!\t",attacker->classname);
	temphp -= (attacker->getatt() - def );
	if(temphp>=hp){
		printf("A MASSIVE 0 damage\t");
	}else{
	printf("A Whopping %d damage!\t",(hp-temphp));
	hp = temphp;
	}
	if(hp <=0){printf("%s has been defeated!\n",this->classname); isalive=false; return true;}
	printf("%s has %dHP remaining!\n",this->classname,hp);
	return false;
}

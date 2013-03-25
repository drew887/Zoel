#include "stdafx.h"
#include "zombie.h"


zombie::zombie(void){
	strcpy(classname,"Zombie");
	hp = maxhp = (rand() % 20 )+ 8;
	def = (rand() % 2 )+ 1;
	att = (rand() % 2 )+ 1;
	inventory = new inven[3];
	inventory[0] = FLESH;
	inventory[1] = CUFFS;
	inventory[2] = BOOTS;
}


zombie::~zombie(void){
	delete [] inventory;
}

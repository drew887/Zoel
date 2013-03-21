#include "stdafx.h"

bool entity::attack(entity * defender){
	return defender->defend(this);
}
bool entity::defend(entity * attacker){
	//char classname[8];
	int temphp = hp;
	printf("%s is attacking!\t",attacker->classname);
	hp -= (attacker->getatt() - def );
	printf("A Whopping %d damage!\t",(temphp-hp));
	if(hp <=0){printf("%s has been defeated!\n",this->classname); isalive=false; return true;}
	printf("%s has %dHP remaining!\n",this->classname,hp);
	return false;
}
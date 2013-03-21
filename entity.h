#pragma once
#include "stdafx.h"
class entity
{
protected:
	int hp;
	unsigned int def;
	unsigned int att;
	inven * inventory;
public:
	char classname[8];
	bool isalive;
	entity(void){
		isalive =true;
	}

	virtual ~entity(void){

	}
	virtual bool attack(entity * defender);
	virtual bool defend(entity * attacker);
	virtual unsigned int getatt(){return att;}
	virtual unsigned int getdef(){return def;}
	virtual unsigned int gethp(){return hp;}

};



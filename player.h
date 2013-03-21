#pragma once
#include "entity.h"
#include "stdafx.h"
class player :public entity{
protected:
	char name[9];

public:
	void save();
	bool load(const char * name);
	Weapon wep;
	player(void);
	player(bool derp);
	~player(void);
	void giveWep(Weapon wepa);
	bool attack(entity * defender);
	bool defend(entity * attacker);
	unsigned int getatt();
	unsigned int reatt();
};


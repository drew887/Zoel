#include "stdafx.h"
#pragma once
enum inven{SHIRT,BOOTS,CUFFS,FLESH};
#pragma pack(1)
struct Weapon{
public:
	unsigned int att;
	unsigned int spd;
	char name[9];
};
#pragma pack()
/*
 * player.cpp
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
#include "room.h"
#include "player.h"
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <string.h>


player::player(void){
	//
	printf("Hello there!\nWhat is your name?\n");
	scanf("%8s", classname);
	//clearin();//we use this to make sure we clean up the input buffer incase they just insterted spam or something trying to cause a buffer overflow D:
	printf("So your name is %s?\nthat certainly is an...interesting name...\n", classname);
	hp = maxhp = (rand() % 8) + 30;
	def = (rand() % 3) + 1;
	att = (rand() % 3) + 1;
	strcpy(wep.name, "None");
	wep.att = 0;
	wep.spd = 0;
	///	printf("Well you have %d HP, %d def, and %d att\nGood luck!\n",hp,def,att);
	stats();
	inventory = new inven[3];
	inventory[0] = SHIRT;
	inventory[1] = CUFFS;
	inventory[2] = BOOTS;
}

player::~player(void){
	delete[] inventory;
}

bool player::attack(entity * defender){
	if (defender == this){ printf("I can't Attack myself!\n"); return true; }
	return defender->defend(this);
}
bool player::defend(entity * attacker){
	if (attacker == this){ printf("I can't Attack myself!\n"); return true; }
	int temphp = hp;
	printf("%s is attacking!\t", attacker->classname);
	temphp -= (attacker->getatt() - def);
	if (temphp >= hp){
		printf("A SUPER FUN 0 damage\t");
	}
	else{
		printf("A Whopping %d damage!\t", (hp - temphp));
		hp = temphp;
	}
	if (hp <= 0){ printf("%s has been defeated!\n", classname); isalive = false; throw DEAD_PLAYER; return true; }
	printf("%s has %dHP remaining!\n", classname, hp);
	return false;
}
void player::giveWep(Weapon wepa){
	strcpy(wep.name, wepa.name);
	wep.att = wepa.att;
	wep.spd = wepa.spd;
}
void player::tellwep(){
	printf("%s\n", wep.name);

}

unsigned int player::getatt(){
	return this->reatt();// + (rand() % wep.spd);
}
unsigned int player::reatt(){
	//printf("THIS %s %d ,%d\t",this->wep.name,(this->att + this->wep.att),this->wep.att);
	if (this->wep.spd == 0){ return this->att + this->wep.att - 1; }
	return this->att + this->wep.att + (rand() % wep.spd);
}
//////////////////////////////////\\\\\\\\\\\\\\\\\>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
void player::save(){
	FILE * pp = fopen(this->classname, "r");
	unsigned char te = 0;
	if (pp){
		printf("File already exsists. Overwrite? y/n\n");
		scanf("%c", &te);
		//clearin();
		switch (te){
		case 'y':
			printf("Overwriteing....\n");
			break;
		default:
			return;
			break;
		}
		fclose(pp);
	}
	pp = fopen(this->classname, "wb");
	if (!pp){ printf("SOME SORT OF FILE IO ERROR, BITCH AT ANDREW TO FIX IT!\n"); return; }
	char check[] = "zoel";
	fwrite(check, sizeof(check), 1, pp);
	fwrite(&att, sizeof(att), 1, pp);
	fwrite(&def, sizeof(def), 1, pp);
	fwrite(&maxhp, sizeof(maxhp), 1, pp);
	fwrite(&hp, sizeof(hp), 1, pp);
	fwrite(&wep, sizeof(Weapon), 1, pp);
	fwrite(classname, sizeof(classname), 1, pp);
	//fwrite(&dep, sizeof(ROOM_ERR), 1, pp);
	fclose(pp);
	printf("Save complete!\n");
}//end player::save/////////////////\\\\\\\\\\\\\\\\\\\\\\\\\\\>>>>>>>>>>>>>>>>>>>>>

bool player::load(const char *name){
	FILE * pp = fopen(name, "rb");
	if (!pp){ printf("File not found, aborting load!\n"); return false; }
	char check[5];
	fread(check, 5, 1, pp);
	if (strncmp(check, "zoel", 4)){ printf("CORRUPT OR IMPROPERLY MODDED SAVE\n"); return false; }
	fread(&att, sizeof(int), 1, pp);
	fread(&def, sizeof(int), 1, pp);
	fread(&maxhp, sizeof(int), 1, pp);
	fread(&hp, sizeof(int), 1, pp);
	if (hp > maxhp){ printf("Modded save file, you can't have more hp then your max hp silly!\n"); exit(0xDEAD); }
	fread(&this->wep, sizeof(Weapon), 1, pp);
	fread(&classname, 9, 1, pp);
	//fread(&dep, sizeof(ROOM_ERR), 1, pp);
	printf("Loaded %s save!\n", this->classname);
	stats();
	fclose(pp);
	return true;
}
void player::stats(){
    printf("Stats:\nMaxhp: %d\thp: %d\natt: %d\t def: %d\nweapon: %s \t att: %d\n", maxhp, hp, att, def, wep.name, wep.att);
}
void player::heal(){
	hp = maxhp;
}

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
#include <string.h>
#include <stdio.h>
#include <iostream>

using namespace std;

player::player(void){
	//
    cout << "Hello there!\nWhat is your name?" << endl;
    getline(cin, classname);
    hp = maxhp = (rand() % 8) + 30;
	def = (rand() % 3) + 1;
	att = (rand() % 3) + 1;
	strcpy(wep.name, "None");
	wep.att = 0;
	wep.spd = 0;
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
    return defender->defend(this);
}
bool player::defend(entity * attacker){
    int temphp = hp;
    cout << attacker->classname <<"is attacking!\t" << endl;
	temphp -= (attacker->getatt() - def);
	if (temphp >= hp){
        cout << "A SUPER FUN 0 damage\t";
	}
	else{
        cout << "A Whopping " << (hp - temphp) << " damage!\t";
		hp = temphp;
	}
    if (hp <= 0){
        cout << classname <<" has been defeated!" << endl;
        isalive = false;
        throw DEAD_PLAYER;
        return true;
    }
    cout << classname << " has " << hp << " remaining!" << endl;
	return false;
}
void player::giveWep(Weapon wepa){
	strcpy(wep.name, wepa.name);
	wep.att = wepa.att;
	wep.spd = wepa.spd;
}
void player::tellwep(){
    cout << wep.name<< endl;
}

unsigned int player::getatt(){
	return this->reatt();// + (rand() % wep.spd);
}
unsigned int player::reatt(){
	//printf("THIS %s %d ,%d\t",this->wep.name,(this->att + this->wep.att),this->wep.att);
    if (wep.spd == 0){
        return att + wep.att - 1;
    }
    return att + wep.att + (rand() % wep.spd);
}
//////////////////////////////////\\\\\\\\\\\\\\\\\>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
void player::save(){
    FILE * pp = fopen(classname.c_str(), "r");
	unsigned char te = 0;
	if (pp){
        cout << "File already exsists. Overwrite? y/n" << endl;
        cin >> te;
        cin.ignore(80,'\n');
		switch (te){
        case 'Y':
		case 'y':
            cout << "Overwriteing...." << endl;
			break;
		default:
			return;
			break;
		}
		fclose(pp);
	}
    pp = fopen(classname.c_str(), "wb");
    if (!pp){
        throw 4;
    }
	char check[] = "zoel";
	fwrite(check, sizeof(check), 1, pp);
	fwrite(&att, sizeof(att), 1, pp);
	fwrite(&def, sizeof(def), 1, pp);
	fwrite(&maxhp, sizeof(maxhp), 1, pp);
	fwrite(&hp, sizeof(hp), 1, pp);
	fwrite(&wep, sizeof(Weapon), 1, pp);
    fwrite(classname.c_str(), classname.length(), 1, pp);
    fclose(pp);
    cout << "Save complete!" << endl;
}//end player::save/////////////////\\\\\\\\\\\\\\\\\\\\\\\\\\\>>>>>>>>>>>>>>>>>>>>>

bool player::load(const char *name){
	FILE * pp = fopen(name, "rb");
    if (!pp){
        cout << "File not found, aborting load!" << endl;
        return false;
    }
	char check[5];
	fread(check, 5, 1, pp);
    if (strncmp(check, "zoel", 4)){
        cout << "CORRUPT OR IMPROPERLY MODDED SAVE" << endl;
        return false;
    }
	fread(&att, sizeof(int), 1, pp);
	fread(&def, sizeof(int), 1, pp);
	fread(&maxhp, sizeof(int), 1, pp);
	fread(&hp, sizeof(int), 1, pp);
    if (hp > maxhp){
        cout << "Modded save file, you can't have more hp then your max hp silly!" << endl;
        exit(0xDEAD);
    }
	fread(&this->wep, sizeof(Weapon), 1, pp);
	fread(&classname, 9, 1, pp);
	//fread(&dep, sizeof(ROOM_ERR), 1, pp);
    cout << "Loaded" << classname <<" save!" << endl;
	stats();
	fclose(pp);
	return true;
}
void player::stats(){
    cout << "Stats:\nName: " << classname << endl <<"Maxhp: "<< maxhp << "\thp: " << hp << "\natt: " << att <<" \t def: " << def << \
            "\nweapon: " << wep.name << "\t att: " << wep.att << endl;//att, def, wep.name, wep.att);
}
void player::heal(){
	hp = maxhp;
}

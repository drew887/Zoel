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

Player::Player(void) {
	srand(time(NULL));
	cout << "Hello there!\nWhat is your name?" << endl;
	getline(cin, classname);
	cout << endl;
	hp = maxhp = (rand() % 8) + 30;
	def = (rand() % 3) + 1;
	att = (rand() % 3) + 1;
	strcpy(wep.name, "None");
	wep.att = 0;
	wep.spd = 0;
	cout << "Welcome " << classname << ", to the world of ZOEL." << endl << endl;
}

Player::~Player(void) {

}

bool Player::attack(Entity * defender) {
	return defender->defend(this);
}
bool Player::defend(Entity * attacker) {
	int temphp = hp;
	cout << attacker->classname << "is attacking!\t" << endl;
	temphp -= (attacker->getatt() - def);
	if (temphp >= hp) {
		cout << "A SUPER FUN 0 damage\t";
	}
	else {
		cout << "A Whopping " << (hp - temphp) << " damage!\t";
		hp = temphp;
	}
	if (hp <= 0) {
		cout << classname << " has been defeated!" << endl;
		isalive = false;
		throw DEAD_PLAYER;
		return true;
	}
	cout << classname << " has " << hp << " remaining!" << endl;
	return false;
}
void Player::giveWep(Weapon wepa) {
	strcpy(wep.name, wepa.name);
	wep.att = wepa.att;
	wep.spd = wepa.spd;
}
void Player::tellwep() {
	cout << wep.name << endl;
}

unsigned int Player::getatt() {
	return this->reatt();
}
unsigned int Player::reatt() {
	if (wep.spd == 0){
		return att + wep.att - 1;
	}
	return att + wep.att + (rand() % wep.spd);
}

void Player::save() {
	FILE * filePointer = fopen(classname.c_str(), "r");
	char input;
	if (filePointer) {
		cout << "File already exsists. Overwrite? y/n" << endl;
		cin >> input;
		cin.ignore(80, '\n');
		while (input != 'y' && input != 'n'){
			cout << "please enter y or n : ";
			cin >> input;
			cin.ignore(80, '\n');
		}
		if (input == 'n'){
			cout << "okay, did not overwrite" << endl;
			return;
		}
		fclose(filePointer);
	}
	filePointer = fopen(classname.c_str(), "wb");
	if (!filePointer){
		throw 4;
	}
	char check[] = "zoel";
	fwrite(check, sizeof(check), 1, filePointer);
	fwrite(&att, sizeof(att), 1, filePointer);
	fwrite(&def, sizeof(def), 1, filePointer);
	fwrite(&maxhp, sizeof(maxhp), 1, filePointer);
	fwrite(&hp, sizeof(hp), 1, filePointer);
	fwrite(&wep, sizeof(Weapon), 1, filePointer);
	int nameLength = classname.length();
	fwrite(&nameLength, sizeof(int), 1, filePointer);
	fwrite(classname.c_str(), classname.length(), 1, filePointer);
	fclose(filePointer);
	cout << "Save complete!" << endl;
}

bool Player::load(const char *name){
	FILE * filePointer = fopen(name, "rb");
	if (!filePointer){
		cout << "File not found, aborting load!" << endl;
		return false;
	}
	char check[5] = {};
	fread(check, 5, 1, filePointer);
	if (strncmp(check, "zoel", 4)){
		cout << "CORRUPT OR IMPROPERLY MODDED SAVE" << endl;
		return false;
	}
	fread(&att, sizeof(int), 1, filePointer);
	fread(&def, sizeof(int), 1, filePointer);
	fread(&maxhp, sizeof(int), 1, filePointer);
	fread(&hp, sizeof(int), 1, filePointer);
	if (hp > maxhp){
		cout << "Modded save file, you can't have more hp then your max hp silly!" << endl;
		exit(0xDEAD);
	}
	fread(&this->wep, sizeof(Weapon), 1, filePointer);
	unsigned int nameLength = 0;
	fread(&nameLength, sizeof(int), 1, filePointer);
	char * tempName = new char[nameLength + 1];
	tempName[nameLength] = 0;
	fread(tempName, nameLength, 1, filePointer);
	classname = tempName;
	delete [] tempName;
	cout << "Loaded " << classname << " save!" << endl;
	stats();
	fclose(filePointer);
	return true;
}
void Player::stats(){
	cout << "Stats:\nName: " << classname << endl << "Maxhp: " << maxhp << "\thp: " << hp << "\natt: " << att << " \t def: " << def << "\nweapon: " << wep.name << "\t att: " << wep.att << endl;
}
void Player::heal(){
	hp = maxhp;
}

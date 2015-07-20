/*
 * player.cpp
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

#include "player.h"
#include "slowout.h"


#include <time.h>
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

using namespace std;

extern zoel::SlowOut slow;

Player::Player(void) {
    srand(int(time(NULL)));
    slow << "Hello there!\nWhat is your name?" << endl;
    slow.print();
    getline(cin, classname);
    cout << endl;
    hp = maxhp = (rand() % 8) + 30;
    def = (rand() % 3) + 3;
    att = (rand() % 5) + 4;
    wep = NULL;
    inventory.push_back(new Item("Clothes"));
    slow << "Welcome " << classname << ", to the world of ZOEL.\nEnter 'help' for a list of commands." << endl << endl;
    slow.print();
}

Player::~Player(void) {

}

bool Player::defend(Entity * attacker) {
    int temphp = hp;
    slow << attacker->classname << " is attacking! ";
    temphp -= (attacker->getAttack() - def);
    if(temphp >= hp) {
        slow << "A SUPER FUN 0 damage ";
    }
    else {
        slow << "A Whopping " << (hp - temphp) << " damage! ";
        hp = temphp;
    }
    if(hp <= 0) {
        slow << classname << " has been defeated!" << endl;
        slow.print();
        isalive = false;
        return true;
    }
    slow << classname << " has " << hp << " remaining!" << endl << endl;
    slow.print();
    return false;
}

unsigned int Player::getAttack() {
    unsigned int result = 0;
    if(wep){
        if(wep->speed > 0){
            result = att + wep->attack + (rand() % wep->speed);
        }
        else {
            result = att + wep->attack;
        }
    }
    else{
        result = att;
    }
    return result;
}

void Player::save() {
    FILE * filePointer = fopen(classname.c_str(), "r");
    char input;
    if(filePointer) {
        slow << "File already exsists. Overwrite? y/n" << endl;
        slow.print();
        cin >> input;
        cin.ignore(80, '\n');
        while(input != 'y' && input != 'n'){
            slow << "please enter y or n : ";
            slow.print();
            cin >> input;
            cin.ignore(80, '\n');
        }
        if(input == 'n'){
            slow << "okay, did not overwrite" << endl;
            slow.print();
            fclose(filePointer);
            return;
        }
        fclose(filePointer);
    }
    filePointer = fopen(classname.c_str(), "wb");
    if(filePointer){
        char check[5] = "zoel";
        fwrite(check, sizeof(check), 1, filePointer);
        fwrite(&att, sizeof(att), 1, filePointer);
        fwrite(&def, sizeof(def), 1, filePointer);
        fwrite(&maxhp, sizeof(maxhp), 1, filePointer);
        fwrite(&hp, sizeof(hp), 1, filePointer);
        int nameLength = classname.length();
        fwrite(&nameLength, sizeof(int), 1, filePointer);
        fwrite(classname.c_str(), classname.length(), 1, filePointer);
        fclose(filePointer);
        slow << "Save complete!" << endl;
    }
    else{
        slow << "Error writing save, aborting!" << endl;
    }
    slow.print();
}

bool Player::load(const char *name){
    FILE * filePointer = fopen(name, "rb");
    if(!filePointer){
        slow << name << " file not found, aborting load!" << endl;
        slow.print();
        return false;
    }
    char check[5] = {};
    fread(check, 5, 1, filePointer);
    if(strncmp(check, "zoel", 4)){
        slow << "CORRUPT OR NOT A ZOEL SAVE" << endl;
        slow.print();
        return false;
    }
    fread(&att, sizeof(int), 1, filePointer);
    fread(&def, sizeof(int), 1, filePointer);
    fread(&maxhp, sizeof(int), 1, filePointer);
    fread(&hp, sizeof(int), 1, filePointer);
    unsigned int nameLength = 0;
    fread(&nameLength, sizeof(int), 1, filePointer);
    char * tempName = new char[nameLength + 1];
    tempName[nameLength] = 0;
    fread(tempName, nameLength, 1, filePointer);
    classname = tempName;
    delete[] tempName;
    slow << "Loaded " << classname << " save!" << endl;
    slow.print();
    stats();
    fclose(filePointer);
    return true;
}

void Player::stats(){
    slow << "Name: " << classname << endl << "Maxhp: " << maxhp << " Hp: " << hp << endl;
    slow << "Attack: " << att << " Defence: " << def << endl;
    if(wep){
        slow << "Weapon: " << wep->name << " Attack: +" << wep->attack << endl;
        slow << "Total attack: " << getAttack() << endl;
    }
    else{
        slow << "No Weapon equipped" << endl;
    }
    slow.print();
}

void Player::heal(){
    hp = maxhp;
}

void Player::printInventory(){
    slow << "Current inventory:" << endl;
    for(unsigned int ctr = 0; ctr < inventory.size(); ctr++){
        slow << inventory[ctr]->name << endl;
    }
    slow.print();
}

#include <typeinfo>

void Player::giveItem(Item * item){
    zoel::SlowOut slow;
    slow << classname << " has recieved: " << item->name << endl;
    if(typeid(Weapon) == typeid(*item)){
        wep = (Weapon*)item;
        slow << "Equiping: " << item->name << endl;
    }
    slow.print();
    inventory.push_back(item);
}

Item * Player::dropItem(string item){
    zoel::SlowOut slow;
    Item * result = NULL;
    if(inventory.size() > 0){
        unsigned int ctr;
        for(ctr = 0; ctr < inventory.size(); ctr++){
            if(inventory[ctr]->name == item){
                break;
            }
        }
        if(ctr < inventory.size()){
            result = inventory[ctr];
            slow << "Dropped " << result->name << endl;
            if(wep == result){
                wep = NULL;
            }
            inventory.erase(inventory.begin() + ctr);

        }
    }
    slow.print();
    return result;
}

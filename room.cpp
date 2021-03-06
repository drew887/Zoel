/*
 * room.cpp
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

#include <iostream>
#include <cstring>

#include "room.h"
#include "player.h"
#include "slowout.h"

using namespace std;
using zoel::SlowOut;
vector<string> Room::tokens = { "north", "east", "south", "west", "quit", "help", "stats", "save", "load", "look", "attack", "faster", "slower", "inventory", "take", "drop", "equip" };

SlowOut slow;

Room::Room(string Description) :description(Description){
    attcount = 0;
    next = NULL;
    for(unsigned int i = 0; i < 4; i++){
        at_dir[i] = NONE;
        attached[i] = NULL;
    }
}

Room::~Room(void){
    for(int i = 0; i < 4; i++){
        attached[i] = NULL;
        at_dir[i] = NONE;
    }
    for(unsigned int enemy = 0; enemy < enemies.size(); enemy++){
        delete enemies[enemy];
    }
    for(unsigned int item = 0; item < items.size(); item++){
        delete items[item];
    }
}

inline room_dir directionSwap(room_dir tw){
    switch(tw){
    case NORTH:
        tw = SOUTH;
        break;
    case SOUTH:
        tw = NORTH;
        break;
    case WEST:
        tw = EAST;
        break;
    case EAST:
        tw = WEST;
        break;
    default:
        tw = NONE;
    }
    return tw;
}

Room * Room::start(Player * playera){

    printDescription();
    if(attcount == 0){
        cerr << "ERR You've fallen into a room with no exits!\nGame over!" << endl;
        return NULL;
    }
    idleLoop(playera);
    return this->next;
}

void Room::printDescription(){
    slow << description;
    if(attcount > 0){
        if(attcount > 1){
            slow << " There are paths to the ";
        }
        else{
            slow << " There is a path to the ";
        }
        for(unsigned int curCon = 0; curCon < attcount; curCon++){
            switch(at_dir[curCon]){
            case NORTH:
                slow << "North";
                break;
            case EAST:
                slow << "East";
                break;
            case SOUTH:
                slow << "South";
                break;
            case WEST:
                slow << "West";
                break;
            default:
                break;
            }
            if(curCon < attcount - 1){
                slow << ", ";
            }
            else{
                slow << ".";
            }
        }
    }
    slow << endl;
    slow.print();
    if(enemies.size() > 0){
        slow << endl;
        for(unsigned int enemy = 0; enemy < enemies.size(); enemy++){
            slow << "There is a " << enemies[enemy]->classname << " here!" << endl;
        }
        slow.print();
    }
    if(items.size() > 0){
        slow << endl;
        for(unsigned int item = 0; item < items.size(); item++){
            slow << "There is a " << items[item]->name << " here!" << endl;
        }
        slow.print();
    }
}

bool Room::addPerson(Entity * person){
    bool success = true;
    if(enemies.size() < ROOM_MAX){
        enemies.push_back(person);
    }
    else{
        success = false;
    }
    return success;
}

void Room::addItem(Item * item){
    items.push_back(item);
}

bool Room::attach(Room * ar, room_dir direct, bool connectBack){
    if(attcount >= 4){
        return false;
    }
    for(unsigned int con = 0; con < attcount; con++){
        if(direct == at_dir[con]){
            cerr << "ERR CON ALREADY USED!" << endl;
            return false;
        }
    }
    attached[attcount] = ar;
    at_dir[attcount] = direct;
    attcount++;
    if(connectBack)
    {
        ar->attach(this, directionSwap(direct));
    }
    return true;
}



Room * Room::getRoomAtDir(room_dir dir){
    Room * temp = NULL;
    for(unsigned char i = 0; i < attcount; i++){
        if(at_dir[i] == dir){
            temp = attached[i];
            break;
        }
    }
    return temp;
}

vector<string> tokenize(string msg){
    vector<string> words;
    char * mesg = new char[msg.size() + 1];
    strcpy(mesg, msg.c_str());
    for(unsigned int character = 0; character < msg.size(); character++){
        mesg[character] = tolower(mesg[character]);
    }
    char * tok = strtok(mesg, " ");
    while(tok != NULL){
        if(strcmp(tok, "the")){
            words.push_back(tok);
        }
        tok = strtok(NULL, " ");
    }
    delete[] mesg;
    return words;
}

void Room::idleLoop(Player *play){
    bool loop = true;
    while(loop){
        cout << endl << "> ";
        string msg;
        getline(cin, msg);
        cout << endl;
        if(msg.size() > 0){
            vector<string> words;
            words = tokenize(msg);
            unsigned int token;
            for(token = 0; token < tokens.size(); token++){
                if(words[0] == tokens[token]){
                    break;
                }
            }
            switch(token){
            case 0:
            case 1:
            case 2:
            case 3:
                next = getRoomAtDir((room_dir)token);
                if(next != NULL){
                    loop = false;
                }
                else{
                    slow << "you can't go that way" << endl;
                    slow.print();
                }
                break;
            case 4: //quit
                loop = false;
                next = NULL;
                return;
                break;
            case 5:
                slow << "The commands are:" << endl;
                slow.print();
                for(unsigned int ctr = 0; ctr < tokens.size(); ctr++){
                    slow << "  " << tokens[ctr] << endl;
                    slow.print();
                }
                break;
            case 6:
                play->stats();
                break;
            case 7:
                play->save();
                break;
            case 8:
                if(words.size() < 2){
                    slow << "please enter a name to load: ";
                    slow.print();
                    std::string name;
                    getline(cin, name);
                    if(play->load(name.c_str())){
                        //TODO: figure out a good way to handle loading
                    }
                }
                else{
                    play->load(words[1].c_str());
                }
                break;
            case 9: //look
                printDescription();
                break;
            case 10: //attack
                if(enemies.size() > 0){
                    string targetMesg = "";
                    string target = "";
                    vector<string> targets;
                    if(words.size() < 2){
                        slow << "Attack what?: " << endl;
                        slow.print();
                        for(unsigned int enemy = 0; enemy < enemies.size(); enemy++){
                            slow << enemies[enemy]->classname << endl;
                            slow.print();
                        }
                        cout << endl;
                        getline(cin, target);
                    }
                    else{
                        target = msg.substr(msg.find(' ')+1);
                    }
                    unsigned int enemy;
                    for(enemy = 0; enemy < enemies.size(); enemy++){
                        if(enemies[enemy]->classname == target){
                            break;
                        }
                    }
                    if(enemy < enemies.size()){
                        if(play->attack(enemies[enemy])){
                            delete enemies[enemy];
                            enemies.erase(enemies.begin() + enemy);
                        }
                    }
                    else{
                        slow << "Couldn't find the " << target << endl;
                        slow.print();
                    }
                }
                else{
                    slow << "There isn't any one to attack!" << endl;
                    slow.print();
                }
                break;
            case 11: //faster
                if(slow.timeStep > 0){
                    slow.timeStep -= 5;
                }
                slow << "The text speed is now: " << slow.timeStep << endl;
                slow.print();
                break;
            case 12: //slower
                slow.timeStep += 5;
                slow << "The text speed is now: " << slow.timeStep << endl;
                slow.print();
                break;
            case 13: // inventory
                play->printInventory();
                break;
            case 14: //take
                if(items.size() > 0){
                    string takeItem;
                    if(words.size() < 2){
                        slow << "Take what?" << endl;
                        for(unsigned int ctr = 0; ctr < items.size(); ctr++){
                            slow << items[ctr]->name << endl;
                        }
                        slow.print();
                        getline(cin, takeItem);
                    }
                    else{
                        takeItem = msg.substr(msg.find(" ") + 1);
                    }
                    unsigned int ctr;
                    for(ctr = 0; ctr < items.size(); ctr++){
                        if(takeItem == items[ctr]->name){
                            break;
                        }
                    }
                    if(ctr < items.size()){
                        play->giveItem(items[ctr]);
                        items.erase(items.begin() + ctr);
                    }
                    else{
                        slow << "There is no " << takeItem << " here" << endl;
                        slow.print();
                    }
                }
                else{
                    slow << "There's nothing to take!" << endl;
                    slow.print();
                }
                break;
            case 15: //drop
                if(play->inventory.size() > 0){
                    string dropName;
                    if(words.size() < 2){
                        slow << "Drop what?" << endl;
                        slow.print();
                        play->printInventory();
                        getline(cin, dropName);
                    }
                    else{
                        dropName = msg.substr(msg.find(' ') + 1);
                    }
                    Item * drop = play->dropItem(dropName);
                    if(drop != NULL){
                        items.push_back(drop);
                    }
                }
                else{
                    slow << play->classname << " doesn't have any items to drop" << endl;
                    slow.print();
                }
                break;
            case 16:
                if(play->inventory.size() > 0){
                    string equipName;
                    if(words.size() < 2){
                        slow << "Equip what?" << endl;
                        slow.print();
                        play->printInventory();
                        getline(cin, equipName);
                    }
                    else{
                        equipName = msg.substr(msg.find(' ') + 1);
                    }
                    play->equipItem(equipName);
                }
                else{
                    slow << play->classname << " doesn't have any items to equip" << endl;
                    slow.print();
                }
                break;
            default:
                slow << "I don't know " << words[0] << endl;
                slow.print();
            }//end switch

            if(enemies.size() > 0){
                for(unsigned int enemy = 0; enemy < enemies.size(); enemy++){
                    if(enemies[enemy]->attack(play)){
                        slow << endl << "GAME OVER!" << endl;
                        slow.print();
                        next = NULL;
                        loop = false;
                    }
                }
            }
        }
    }
}

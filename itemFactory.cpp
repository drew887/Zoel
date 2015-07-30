/*
* itemFactory.cpp
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

#include "itemFactory.h"


Item * ItemFactory::readFromFile(FILE * filePointer){
    Item * result = NULL;
    if(filePointer){
        char type;
        fread(&type, 1, 1, filePointer);
        int nameSize = 0;
        fread(&nameSize, sizeof(int), 1, filePointer);
        if(nameSize > 0){
            char * pName = new char[nameSize + 1];
            pName[nameSize] = 0;
            fread(pName, 1, nameSize, filePointer);
            switch(type) {
            case 'I':
                result = new Item(pName);
                break;
            case 'W':
                int attack, speed;
                fread(&attack, sizeof(int), 1, filePointer);
                fread(&speed, sizeof(int), 1, filePointer);
                result = new Weapon(pName, attack, speed);
                break;
            default:
                break;
            }
            delete[] pName;
        }
    }
    return result;
}

Item * ItemFactory::spawnRandomItem(){
    return NULL;
}


Weapon * ItemFactory::spawnRandomWeapon(){
    return NULL;
}

/*
* enemyFactory.cpp
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

#include "enemyFactory.h"

vector<string> EnemyFactory::enemyTypes = { "Slime", "Thief", "Zombie" };

EnemyFactory::EnemyFactory(){
}

Entity * EnemyFactory::spawn(string type){
    Entity * result = NULL;
    unsigned int enemy;
    for(enemy = 0; enemy < enemyTypes.size(); enemy++){
        if(type == enemyTypes[enemy]){
            break;
        }
    }
    switch(enemy){
    case 0:
        result = spawnSlime();
        break;
    case 1:
        result = spawnThief();
        break;
    case 2:
        result = spawnZombie();
        break;
    default:
        result = spawnRandom();
        break;
    }
    return result;
}

Entity * EnemyFactory::spawnRandom(){
    unsigned int type = rand() % 2;
    Entity * result = NULL;
    switch(type){
    case 0:
        result = new Slime();
        break;
    case 1:
        result = new Thief();
        break;
    default:
        result = new Zombie();
        break;
    }
    return result;
}

Zombie * EnemyFactory::spawnZombie(){
    return new Zombie();
}

Slime * EnemyFactory::spawnSlime(){
    return new Slime();
}

Thief * EnemyFactory::spawnThief() {
    return new Thief();
}
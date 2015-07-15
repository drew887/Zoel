/*
 * Zoel.cpp
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
#include "soundEng.h"
#include "zombie.h"
#include "world.h"
#include "inventory.h"
#include "enemyFactory.h"

#include <iostream>
#include <fstream>
#include <cstring>


void opening(int,char**);

int main(int argc, char * argv[]){
    opening(argc,argv);
    World world;
    //EnemyFactory factory;
    if(world.load("zoel.ini")){
        SoundEng::getInstance().play(0);
        Player one;
        Room * currentRoom = world.maps[0]->rooms[0];
        world.maps[0]->rooms[0]->addItem(Item("Key"));
        while(currentRoom != NULL){
            currentRoom = currentRoom->start(&one);
        }
    }
    std::cout << "\nPress enter to continue...\n";
    std::cin.ignore(80, '\n');
    return 0;
}

extern void crossPlatformGetLine(ifstream &, string &);

void opening(int argc, char * argv[]){
    if(argc < 2){
        cout << "Zoel  Copyright (C) 2013 - 2015 Andrew Mcdonald < drew887121@gmail.com >\nThis program comes with ABSOLUTELY NO WARRANTY; This is free software, and you are welcome to redistribute it under certain conditions. See COPYING  or rerun with -legal for details" << endl << endl << endl;
    }
    else if(!strncmp(argv[1],"-legal",6)){
        ifstream fin("COPYING");
        if(fin.is_open()){
            string line;
            while(!fin.eof()){
                crossPlatformGetLine(fin, line);
                cout << line << endl;
            }
            exit(0);
        }
        else{
            cerr << "ERR COPYING is supposed to be included with the release of Zoel\nPlease check with your distributor as to why it is missing" << endl;
            exit(-1);
        }
    }
    else{
        cerr << "ERR usage is " << argv[0] << endl << "or " << argv[0] << " -legal for legal and copyright info" << endl;
        exit(-1);
    }
}

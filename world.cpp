/*
* world.cpp
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

#include "world.h"
#include "exitroom.h"
#include <fstream>
#include <iostream>

using namespace std;

World::World(){

}

World::~World(){
    for(unsigned int map = 0; map < maps.size(); map++){
        delete maps[map];
    }
}

extern room_dir determineDir(char d);

void crossPlatformGetLine(ifstream & fin, string & line){
    string tempLine;
    getline(fin, tempLine);
    if(tempLine[tempLine.size() - 1] == '\r'){ //lets get rid of those pesky CR's windows likes to stick everywhere
        line = tempLine.substr(0, tempLine.size() - 1);
    }
    else{
        line = tempLine;
    }
}

bool World::load(string filename){
    bool result = true;
    ifstream fin(filename);
    if(fin.is_open()){
        string input;
        crossPlatformGetLine(fin, input);
        if(input == "maps"){
            while(!fin.eof()){
                crossPlatformGetLine(fin, input);
                if(input.empty()){
                    continue;
                }
                if(input == "spam"){
                    break;
                }
                maps.push_back(new Map(input));
                Map * last = maps.back();
                last->load(input);
            }
            if(!fin.eof()){
                crossPlatformGetLine(fin, input);
                if(input == "exit"){
                    string connection;
                    while(!fin.eof()){
                        string line, cons;
                        crossPlatformGetLine(fin, line);
                        int lineBreak, chevron, roomNo, conNo;
                        char direction = 0;
                        if(line == "tixe" || input == "tixe" || connection == "tixe"){
                            break;
                        }
                        chevron = line.find(">");
                        lineBreak = line.find("|");
                        input = line.substr(0, chevron);
                        connection = line.substr(chevron + 1, lineBreak - chevron - 1);
                        cons = line.substr(lineBreak + 1);
                        roomNo = atoi(cons.c_str());
                        chevron = cons.find(">");
                        lineBreak = cons.find("|");
                        conNo = atoi(cons.substr(chevron + 1).c_str());
                        direction = cons.substr(lineBreak + 1)[0];
                        if(input.empty() || connection.empty() || line.empty()){
                            continue;
                        }
                        Map * in = getMapByName(input);
                        if(in){
                            Map * con = getMapByName(connection);
                            if(con){
                                in->rooms.push_back(new Exitroom("TX", con, conNo));
                                in->connectRoom(roomNo, in->rooms.size() - 1, determineDir(direction), false);
                            }
                            else{
                                cerr << "ERR MAP " << connection << " NOT FOUND" << endl;
                                result = false;
                            }
                        }
                        else{
                            cerr << "ERR MAP " << input << " NOT FOUND" << endl;
                            result = false;
                        }
                    }
                }
            }
        }
        else{
            cerr << "ERR NO MAPS IN " << filename << ". OR IT IS IMPROPERLY WRITTEN" << endl;
            result = false;
        }
    }
    else{
        cout << "ERROR " << filename << " NOT FOUND!" << endl;
        result = false;
    }
    return result;
}

Map * World::getMapByName(string name){
    Map * result = NULL;
    for(unsigned int map = 0; map < maps.size(); map++){
        if(maps[map]->name == name){
            result = maps[map];
            break;
        }
    }
    return result;
}

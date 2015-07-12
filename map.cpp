/*
* map.cpp
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

#include "map.h"
#include "soundEng.h"

#include <iostream>
#include <string.h>

using namespace std;

class zoelMapVersion{
public:
    zoelMapVersion(char letter, char major, char minor){
        CUR_VER_LETTER = letter;
        CUR_VER_MAJOR = major;
        CUR_VER_MINOR = minor;
    }
    void print(){
        cout << "VERSION " << CUR_VER_LETTER << (int)CUR_VER_MAJOR << '.' << (int)CUR_VER_MINOR << endl;
    }
    void write(FILE * filePointer) const {
        fwrite(&CUR_VER_LETTER, 1, 1, filePointer);
        fwrite(&CUR_VER_MAJOR, 1, 1, filePointer);
        fwrite(&CUR_VER_MINOR, 1, 1, filePointer);
    }
    bool operator== (const zoelMapVersion & other){
        bool result = false;
        if(CUR_VER_LETTER == other.CUR_VER_LETTER){
            if(CUR_VER_MAJOR == other.CUR_VER_MAJOR){
                if(CUR_VER_MINOR == other.CUR_VER_MINOR){
                    result = true;
                }
            }
        }
        return result;
    }
    unsigned char CUR_VER_LETTER;
    unsigned char CUR_VER_MAJOR;
    unsigned char CUR_VER_MINOR;
};



Map::Map(string Name) :name(Name){
    songNo = 0;
}


Map::~Map(){
    for(unsigned int ctr = 0; ctr < rooms.size(); ctr++){
        delete rooms[ctr];
    }
}

void Map::connectRoom(unsigned int one, unsigned int two, room_dir dir, bool twoWay){
    if((one != two) && (one < rooms.size()) && (two < rooms.size())){
        rooms[one]->attach(rooms[two], dir, twoWay);
    }
}

struct room_t{
    string desc;
    vector<int> connections;
    vector<char>directions;
};

room_dir determineDir(char dir){
    room_dir direction = NONE;
    switch(dir){
    case 'N':
        direction = NORTH;
        break;
    case 'E':
        direction = EAST;
        break;
    case 'S':
        direction = SOUTH;
        break;
    case 'W':
        direction = WEST;
        break;
    }
    return direction;
}

bool Map::load(std::string filename){
    bool loaded = true;
    vector<room_t> room_types;
    FILE * filePointer = fopen(filename.c_str(), "rb");
    if(filePointer){
        char check[5] = {};
        fread(check, 4, 1, filePointer);
        if(!strncmp(check, "ZMAP", 4)){
            //---
            char ver[3] = {};
            fread(&ver, 3, 1, filePointer);
            zoelMapVersion version(ver[0], ver[1], ver[2]);
            unsigned int nameSize = 0;
            fread(&nameSize, sizeof(int), 1, filePointer);
            char * cname = new char[nameSize + 1];
            cname[nameSize] = 0;
            fread(cname, nameSize, 1, filePointer);
            name = cname;
            delete[] cname;
            //---
            fread(check, 4, 1, filePointer);
            if(!strncmp(check, "SONG", 4)){
                unsigned int songLength = 0;
                fread(&songLength, sizeof(int), 1, filePointer);
                char * songName = new char[songLength + 1];
                songName[songLength] = 0;
                fread(songName, songLength, 1, filePointer);
                string song = songName;
                delete[] songName;
                songNo = soundEng::getInstance().getNumSongs();
                soundEng::getInstance().addSong(song);
            }
            else{
                fseek(filePointer, -4, SEEK_CUR);
            }
            unsigned int numRooms = 0;
            fread(&numRooms, sizeof(int), 1, filePointer);
            for(unsigned int loop = 0; loop < numRooms; loop++){
                fread(check, 4, 1, filePointer);
                if(!strncmp(check, "ROOM", 4)){
                    room_t room;
                    unsigned int descLength = 1;
                    fread(&descLength, sizeof(int), 1, filePointer);
                    char * tDesc = new char[descLength + 1];
                    tDesc[descLength] = 0;
                    fread(tDesc, descLength, 1, filePointer);
                    room.desc = tDesc;
                    delete[] tDesc;
                    unsigned int roomCount = 0;
                    fread(&roomCount, sizeof(int), 1, filePointer);
                    for(unsigned int ctr = 0; ctr < roomCount; ctr++){
                        unsigned int num = 0;
                        char dir = 'N';
                        fread(&num, sizeof(int), 1, filePointer);
                        fread(&dir, sizeof(char), 1, filePointer);
                        room.connections.push_back(num);
                        room.directions.push_back(dir);
                    }
                    room_types.push_back(room);
                    rooms.push_back(new Room(room.desc.c_str()));
                }
                else{
                    cout << "ERR READING ROOM" << endl;
                }
            }
            for(unsigned int ctr = 0; ctr < room_types.size(); ctr++){
                for(unsigned int loop = 0; loop < room_types[ctr].connections.size(); loop++){
                    connectRoom(ctr, room_types[ctr].connections[loop], determineDir(room_types[ctr].directions[loop]), false);
                }
            }
        }
        else{
            cout << "File is not a valid ZMAP" << endl;
            loaded = false;
        }
        fclose(filePointer);
    }
    else{
        cout << "File " << filename << " not found!" << endl;
        loaded = false;
    }
    return loaded;
}


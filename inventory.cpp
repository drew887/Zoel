#include "inventory.h"

using namespace std;

//Item

Item::Item(string Name){
    name = Name;
}

Item::Item(FILE * filePointer){
    if(filePointer){
        int nameSize = 0;
        fread(&nameSize, sizeof(int), 1, filePointer);
        if(nameSize > 0){
            char * pName = new char[nameSize + 1];
            pName[nameSize] = 0;
            fread(pName, 1, nameSize, filePointer);
            name = pName;
            delete[] pName;
        }
    }
    else{
        name = "ERR READING FROM FILE";
    }
}

void Item::write(FILE * filePointer){
    if(filePointer){
        int nameSize = name.length();
        fwrite(&nameSize, sizeof(int), 1, filePointer);
        fwrite(name.c_str(), 1, nameSize, filePointer);
    }
}

//Weapon

Weapon::Weapon() : Item("None"){
    attack = speed = 0;
}

Weapon::Weapon(string Name, unsigned int att, unsigned int spd) :Item(Name){
    attack = att;
    speed = spd;
}

//Armour
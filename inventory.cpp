#include "inventory.h"

using namespace std;

//Item

Item::Item(string Name){
    name = Name;
}

void Item::write(FILE * filePointer){
    if(filePointer){
        char type = 'I';
        fwrite(&type, 1, 1, filePointer);
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

void Weapon::write(FILE * filePointer){
    if(filePointer){
        char type = 'W';
        fwrite(&type, 1, 1, filePointer);
        int nameSize = name.length();
        fwrite(&nameSize, sizeof(int), 1, filePointer);
        fwrite(name.c_str(), 1, nameSize, filePointer);
        fwrite(&attack, sizeof(int), 1, filePointer);
        fwrite(&speed, sizeof(int), 1, filePointer);
    }
}

// TODO: Armour
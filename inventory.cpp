#include "inventory.h"

using namespace std;

Item::Item(string Name){
    name = Name;
}

Weapon::Weapon() : Item("None"){
    attack = speed = 0;
}

Weapon::Weapon(string Name, unsigned int att, unsigned int spd) :Item(Name){
    attack = att;
    speed = spd;
}
#include "map.h"

using std::string;
map::map(string description) :desc(description)
{

}


map::~map()
{
}

void map::connectRoom(unsigned int one, unsigned int two, room_dir dir, bool twoWay){
	if ((one < rooms.size()) && (two < rooms.size())){
		rooms[one].attach(&rooms[two], dir, twoWay);
	}
}

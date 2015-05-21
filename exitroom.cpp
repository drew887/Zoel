#include "exitroom.h"
#include <iostream>

exitroom::exitroom(const char * desc, map * next, unsigned int start):room(desc){
  nextMap = next;
  if (start < next->rooms.size()){
	  startingRoom = start;
  }
  else{
	  std::cerr << "WARNING STARTING ROOM LARGER THAN AMOUNT OF ROOMS!!" << std::endl;
	  startingRoom = next->rooms.size();
  }
}

room * exitroom::start(player * play){
	std::cout << "\nNow entering the " << nextMap->description << "\n\n";
    return nextMap->rooms[startingRoom];
}

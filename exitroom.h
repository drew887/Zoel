#ifndef EXITROOM_H
#define EXITROOM_H

#include "room.h"
#include "map.h"
#include "player.h"

class exitroom: public room{
 public:
  exitroom(const char * desc, map * next, unsigned int start = 0);
  map * nextMap;
  unsigned int startingRoom;
  virtual room * start(player * play);

};


#endif

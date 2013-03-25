#include "exitroom.h"
#include "stdafx.h"
exitroom::exitroom(ROOM_ERR loc){
    switch(loc){
    case SUBWAY:
	direc = loc;
    break;
    case MAIN_STREET:
	direc = loc;
    break;
    case ROOM_DONE:
    direc = loc;
    break;
    default:
    break;
    }
}

room * exitroom::start(player *playera){
throw direc;
return NULL;
}

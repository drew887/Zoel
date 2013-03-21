#include "stdafx.h"
#pragma once
#ifndef EXITROOM_H
#define EXITROOM_H

class exitroom:public room{
public:
    exitroom(ROOM_ERR loc);
    room * start(player *playera);
    ROOM_ERR direc;
};

#endif // EXITROOM_H

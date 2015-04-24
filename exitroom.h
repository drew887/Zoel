/*
 * exitroom.h
 * This file is part of Zoel
 *
 * Copyright (C) 2013 - Andrew Mcdonald
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

#ifndef EXITROOM_H
#define EXITROOM_H
#include "room.h"
#include "player.h"

class exitroom:public room{
public:
    exitroom(ROOM_ERR loc);//simple change to the room to make it an exit instead. probably didnt have to make a whole new class, but i did it anyway, im taking inspiration from cave jonson D:<
    room * start(player *playera);
    ROOM_ERR direc;
};

#endif // EXITROOM_H

/*
 * inventory.h
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
#include "stdafx.h"
#pragma once
#ifndef INVEN
#define INVEN
enum inven{SHIRT,BOOTS,CUFFS,FLESH};
#pragma pack(1)
#pragma pack(1)
class item{
public:
    item(){}
    virtual ~item(){}
    char name[9];
};

#pragma pack()
struct Weapon{
public:
	unsigned int att;
	unsigned int spd;
	char name[9];
};
#pragma pack()
#endif

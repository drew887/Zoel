/*
 * hoot.h
 * This file is part of Zoel
 *
 * Copyright (C) 2013 - 2015 - Andrew Mcdonald
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

#ifndef HOOT_H
#define HOOT_H
#include <stdlib.h>
#include <stdio.h>
#include <AL/al.h>
#include <AL/alc.h>

#pragma pack(1)
struct buffI{
    short format;
    short channelnum;
    int freq;
    int byterate;
    short BlockAlign;
    short bytesper;
};
#pragma pack()
//
#pragma pack(1)
struct buffD {
    int size;
    int * data;
};
#pragma pack()

class Wav {
public:
    Wav(const char * loc);
    ~Wav();
    buffI Bufdat;
    buffD data;
    ALenum format;
protected:
    void detfmt();		//detect format
};

class Hoot2d {
public:
    Hoot2d();
    ~Hoot2d();
    ALCdevice * device;
    ALCcontext * context;
};

class Source {
public:
    Source(const char * loc);
    ~Source();
    Wav * wave;
    ALuint buffer, source;
    void play();
    void pause();
    void stop();
private:
};

#endif
/*
 * wavloader.cpp
 * This file is part of Zoel
 *
 * Copyright (C) 2012 - 2015 - Andrew Mcdonald
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


#include "hoot.h"

Wav::~Wav(){
    delete[] data.data;
}

Wav::Wav(const char * loc){
    FILE * pp;
    pp = fopen(loc, "rb");
    if(pp == NULL){ throw 4; return; }
    fseek(pp, 20, SEEK_SET);
    fread(&Bufdat, sizeof(Bufdat), 1, pp);
    fseek(pp, 40, SEEK_SET);
    fread(&data.size, 4, 1, pp);
    data.data = new int[data.size];
    fread(data.data, data.size, 1, pp);
    fclose(pp);
    detfmt();
}

void Wav::detfmt(){
    switch(Bufdat.channelnum){
    case 1: 	//mono
        switch(Bufdat.bytesper){
        case 8:
            format = AL_FORMAT_MONO8;
            break;
        case 16:
            format = AL_FORMAT_MONO16;
            break;
        }
        break;

    case 2:		//stereo
        switch(Bufdat.bytesper){
        case 8:
            format = AL_FORMAT_STEREO8;
            break;
        case 16:
            format = AL_FORMAT_STEREO16;
            break;
        }
        break;
    }
}

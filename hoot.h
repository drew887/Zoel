/*
 * hoot.h
 * This file is part of Zoel
 *
 * Copyright (C) 2013 - Andrew Mcdonald
 *
 * Zoel is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 3 of the License, or (at your option) any later version.
 * 
 * Zoel is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 */

#pragma once
#ifndef _HOOT
#define _HOOT
#include <stdlib.h>
#include <stdio.h>
#include <AL/al.h>
#include <AL/alc.h>

//this is actually from openENG, but i own ENG so i can relisence it ;D
//basically this is just some classes and structs for reading in .wav files and playing them with openAL. Joel if you want, this would be useable in your zork clone and you wouldnt have to change anything :D
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
		buffD data; 		//obvious
		ALenum format;
	protected:
		void detfmt();		//detect format
};

class Hoot2d {
	public:
		Hoot2d (); //con
		~Hoot2d (); //decon
		ALCdevice * device; 
		ALCcontext * context;
	private:
		//nothing yet, not really worried about security yet
};

class Source {
	public:
		Source (const char * loc);
		~Source ();
		Wav * wave;
		ALuint buffer, source;
		void play();		//these next three are pretty obvious
		void pause();
		void stop();
	private:
};

//begin Mod
class Mod {
	public:
		Mod (const char * loc);
		~Mod ();
		void play();
		void stop();
	private:
		/* data */
};
//end Mod
#endif







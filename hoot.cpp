/*
 * hoot.cpp
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


#include "hoot.h"

Hoot2d::~Hoot2d(){
	alcMakeContextCurrent(NULL);
	alcDestroyContext(context);
	alcCloseDevice(device);
}

Hoot2d::Hoot2d(){
	alGetError();
	device = alcOpenDevice(NULL);				//create the easiest available sound device
	context = alcCreateContext(device, 0);		//create a context to handle the device
	alcMakeContextCurrent(context);				//turn the context on and focus on it
	//Now we will set up where the "listener" is; the listener is the where the user is, and this is only importand if you want to have 3d sound, but must still exsist.
	alListener3f(AL_POSITION, 0, 0, 0);			//this is a general function used to edit several attr of the listener, ie position
	alListener3f(AL_VELOCITY, 0, 0, 0);
	alListener3f(AL_ORIENTATION, 0, 0, -1);
}

Source::~Source(){
	this->stop();
	alDeleteSources(1, &source);
	alDeleteBuffers(1, &buffer);
}

Source::Source(const char * loc){
	try{
		wave = new Wav(loc);
	}
	catch (int e){
		if (e == 4){
			printf("wav file not found, aborting construction of Source!\n");
			return;
		}
	}
	alGenSources(1, &source);				//Here we generated 1 source and pointed to our source variable
	alSourcef(source, AL_PITCH, 1.0);				//this is like the one for Listeners, except now we point to a source as well
	alSourcef(source, AL_GAIN, 1);
	alSource3f(source, AL_POSITION, 0, 0, 0);			//It is located at 0,0,0; note how well this will work with OPENGL ;D
	alSource3f(source, AL_VELOCITY, 0, 0, 0);			//It isn't going to move yet, so it's velocity is 0 ;D
	alSourcei(source, AL_LOOPING, AL_TRUE);			//We tell it to loop the file.
	//So now we have a source, all we need is a buffer to hold the sound info itself.
	alGenBuffers(1, &buffer);				//We have again generated 1 buffer, now it is time to read data from a file and yay.
	alBufferData(buffer, wave->format, wave->data.data, wave->data.size, wave->Bufdat.freq);
	alSourcei(source, AL_BUFFER, buffer);
	delete wave;
	wave = 0;
}

void Source::play(){
	alSourcePlay(source);
}

void Source::pause(){
	alSourcePause(source);
}

void Source::stop(){
	alSourceStop(source);
}

/*
 * wavloader.cpp
 * This file is part of Zoel
 *
 * Copyright (C) 2012 - Andrew Mcdonald
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

Wav::~Wav(){
	//printf("THIS IS A WAV DECONSTRUCTOR\n");
	delete[] data.data;
}

Wav::Wav(const char * loc){
char t;
	FILE * pp;
	pp = fopen(loc, "rb");
	if(pp==NULL){throw 4;return;}
	fseek(pp,20,SEEK_SET);
	t = fread(&Bufdat,sizeof(Bufdat),1,pp);
	//printf("%d %d %d %d %d %d\n",Bufdat.format,Bufdat.channelnum,Bufdat.freq,Bufdat.byterate,Bufdat.BlockAlign,Bufdat.bytesper);
	fseek(pp,40,SEEK_SET);
	t = fread(&data.size,4,1,pp);
	//printf("%d\n",data.size);
	data.data = new int[data.size];
	t = fread(data.data,data.size,1,pp);
	fclose(pp);
	detfmt();
}

//begin Wav::detfmt
void Wav::detfmt(){
	switch(Bufdat.channelnum){
		case 1: 	//mono
			switch(Bufdat.bytesper){
				case 8:
					format = AL_FORMAT_MONO8;
					//printf("MON8\n");
				break;
				case 16:
					format = AL_FORMAT_MONO16;
					///printf("MON16\n");
				break;
			}
		break;

		case 2:		//stereo
			switch(Bufdat.bytesper){
				case 8:
					format = AL_FORMAT_STEREO8;
					//printf("STER8\n");
				break;
				case 16:
					format = AL_FORMAT_STEREO16;
					//printf("STER16\n");
				break;
			}
		break;
	}//end main switch
}
//end Wav::detfmt()


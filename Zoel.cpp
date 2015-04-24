/*
 * Zoel.cpp
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
// Zoel.cpp
#include "player.h"
#include "room.h"
#include "hoot.h"
#include "inventory.h"
#include "healroom.h"
#include "exitroom.h"
#include "zombie.h"
#include <stdio.h>
#include <string.h>
#include <signal.h>
ROOM_ERR dep;
char opening[] = "You awake again in the train you were in when the cataclysm happened.\nYou check your pack and find that you have finally run out of food.\nYou've heard some very disturbing noises over the past couple days.\nThankfully you've been able to keep yourself hidden, rationing your food.\nYou grab your head as you stumble onto your feet, looks like its time to find\nsome food. You walk off the subway car and into the tunnel.\nThe door of the train closes behind you before finally losing power\n....seems like there's no hiding now....\nYou find your trusty knife still in your pack!\n";
char bigmap[200];
unsigned char curmapnum;
char mapnum[10];
room * rooms[10];
room * exitr;
room * conecter;
Hoot2d * hoot = new Hoot2d();
Source * back = new Source("sub.wav");
player * Me;
Weapon Sword;
entity * tes[6];
room * rom = NULL;
int main(int argc, char* argv[]){
	//int * dummy = new int(4);
	signal(SIGINT, exit);
	atexit(enter);
	Sword.att = 4;
	Sword.spd = 2;
	strncpy(Sword.name, "Knife", sizeof("Knife"));
	printf("Welcome to Zoel; a wonderful little Zork clone based on Joel\nLoad a previous character? y or any thing else for new game\n");
	//	fflush(stdout);
	unsigned char te = 0;
	scanf("%c", &te);
	//clearin();
	if (te == 'q'){ exit(0); }
	if (te == 'y'){
		printf("Enter a name then..\n");
		char name[9];
		scanf("%8s", name);
		//clearin();
		Me = new player(true);
		try{
			if (!(Me->load(name))){
				printf("Starting a new game then. you can try loading again once play starts\n"); delete Me; Me = NULL;
				Me = new player();
				back->play();
				printf(opening);
				Me->giveWep(Sword);
			}
		}
		catch (ROOM_ERR e){ back->play(); }
	}
	else{
		Me = new player();
		back->play();
		printf(opening);
		Me->giveWep(Sword);
	}
	startup();
	rom = rooms[9];
	bool go = true;
	//////////////////////////////////////////////////////////////main game loop
	while (go){
		if (rom){
			try{
				rom = rom->start(Me);
			}
			catch (ROOM_ERR e){
				if (catcher(e)){ go = false; }
			}
		}
		else{ go = false; printf("SOME SORT OF POINTER ERROR\nBitch at andrew to fix!\n"); }
	}//end while
	return 0;
}
void leave(){
	for (int i = 0; i < 10; i++){
		delete rooms[i];
		rooms[i] = NULL;
	}
	delete exitr;
	exitr = NULL;
	delete conecter;
	conecter = NULL;
	for (char i = 0; i < 6; i++){ delete tes[i]; tes[i] = NULL; }
}
#include <iostream>
void enter(void){
	leave();
	delete Me;
	delete back;
	delete hoot;
	std::cout << "\nPress enter to continue...\n";
	std::cin.ignore(1, '\n');
}
bool catcher(ROOM_ERR e){
	switch (e){
	case SUBWAY:
		printf("You are now in the subway\n");
		leave();
		startup();
		//try{
		rom = rooms[9];
		//}catch(ROOM_ERR fe){}
		break;
	case MAIN_STREET:
		printf("You are now on mainstreet\n");
		leave();
		//mainstreet();
		rom = rooms[0];
		break;
	case ALL_CON_USED:
		printf("ALL_CON\n");
		exit(0xDEAD);
		break;
	case ROOM_FULL:
		printf("ROOM_FULL\n");
		exit(0xDEAD);
		break;
	case CON_ALREADY_USED:
		printf("THAT CON USED\n");
		exit(0xDEAD);
		break;
	case DEAD_PLAYER:
		printf("you died :(\n");
		printf("Game over\n");
		exit(0xDEAD);
		break;
	case ROOM_DONE:
		printf("You win!\nThanks for beta testing Zoel, I very much appreciate it :D\nYou can send errors to drew887 or post them on github.\nRemember to get the newest release ;D\n");
		return true;
		break;
	case NO_ROOMS_ATTACHED:
		printf("You made it into a nightmare room with no exits!\n......Game over.....\n");
		exit(0xDEAD);
		break;
	case LOADED_RES:
		leave();
		startup();
		//try{
		rom = rooms[0];
		//}catch(ROOM_ERR fe){}
		break;
	}
	return false;
}//end catcher
void startup(){
	char starmaps[] = "-%c-\t-%c-\t- -\t- -\t- -\t-|\n\t | \t   \t   \t   \t |\n\t %c-\t-%c \t %c- \t-%c-\t-%c\n\t   \t   \t | \t | \t  \n\t   \t %c-\t-%c-\t-%c\n";
	char starnum[] = { '9', '8', '7', '6', '1', '4', '5', '2', '0', '3' };
	curmapnum = 0;
	strcpy(mapnum, starnum);
	strcpy(bigmap, starmaps);
	FILE * pp = fopen("one", "rb");
	char * tempdesc;
	if (!pp){ printf("Corrupt or improper story file for the subway.\nPlease ask Andrew about this or redownload the story files\n"); exit(0xDEAD); }
	unsigned int count = 0;
	dep = ROOM_DONE;
	for (char i = 0; i < 6; i++){ tes[i] = new zombie(); }
	exitr = new exitroom(MAIN_STREET);
	for (int i = 0; i < 10; i++){
		fread(&count, 4, 1, pp);
		if (feof(pp)){ printf("Corrupt or improper story file for the subway. %d\nPlease ask Andrew about this or redownload the story files\n", i); exit(0xDEAD); }
		tempdesc = new char[count + 1];
		fread(tempdesc, count, 1, pp);
		tempdesc[count] = '\0';
		if (feof(pp)){ printf("Corrupt or improper story file for the subway. %d\nPlease ask Andrew about this or redownload the story files\n", i); exit(0xDEAD); }
		if (i == 5){
			rooms[i] = new healroom(tempdesc, i);
		}
		else{
			rooms[i] = new room(tempdesc, i);
		}
		delete[] tempdesc;
		tempdesc = NULL;
		//printf("%s\n",tempdesc);
	}
	fclose(pp);
	// for (char i = 7; i<10;i++){rooms[i] = new room("RANDOM ROOM");}
	//room0
	rooms[0]->attach(rooms[1], NORTH, true);
	rooms[0]->attach(rooms[2], WEST, true);
	rooms[0]->attach(rooms[3], EAST, true);
	//room1
	//rooms[1]->attach(rooms[2],WEST,true);
	rooms[1]->attach(rooms[4], EAST, true);
	rooms[1]->addper(tes[0]);
	//room2
	rooms[2]->attach(rooms[6], NORTH, true);
	rooms[2]->addper(tes[2]);
	//room3
	rooms[3]->attach(rooms[4], NORTH, true);
	rooms[3]->addper(tes[1]);
	//room4
	rooms[4]->attach(rooms[5], EAST, true);
	//room5
	rooms[5]->attach(rooms[8], NORTH);
	rooms[5]->addper(tes[3]);
	//room6
	rooms[6]->attach(rooms[7], WEST, true);
	//room7
	rooms[7]->attach(rooms[8], NORTH, true);
	rooms[7]->addper(tes[4]);
	//rooms[8]
	rooms[8]->attach(rooms[9], WEST, true);
	rooms[8]->attach(rooms[5], EAST);
	rooms[8]->addper(tes[5]);
	//rooms[9]
	rooms[9]->attach(exitr, WEST);
}

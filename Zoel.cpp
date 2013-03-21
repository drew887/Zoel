// Zoel.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
//
room * rooms[10];
player * Me;
Weapon Sword;
zombie fred;
zombie tes[3];
room * rom = NULL;
int main(int argc, char* argv[]){
	atexit(enter);
	mprintf("Welcome to Zoel; a wonderful little Zork clone based on Joel\nLoad a previous character? y or n for new game\n");
//	fflush(stdout);
	unsigned char te = 0;
	scanf("%c", &te);
	clearin();
	if(te == 'y'){
	    Me = new player(true);
	    mprintf("Enter a name then..\n");
	    char name[9];
	    scanf("%8s",name);
	    clearin();
	    try{
	    if(!(Me->load(name))){mprintf("Starting a new game then. you can try loading again once play starts\n");delete Me; Me = NULL; Me = new player();}
	}catch(ROOM_ERR e){printf("derp\n");}
	}else{
	    Me = new player();
	    printf("herp\n");
	}
	mprintf("You awake from the after math of an interesting event to find\nyourself in a fiery remnant of the city you used to live in...\nYou grab your head as you stumble onto your feet, dizzy and\nconfused you walk off the subway car and into the tunnel.\nThe door of the train closes behind you before finally losing power,\nseems like there's no hiding now...\n");
		Sword.att = 4;
        Sword.spd = 2;
	strncpy(Sword.name,"Knife",sizeof("Knife"));
	mprintf("You find your trusty knife still in your pack!\n");
	Me->giveWep(Sword);
	startup();
	try{
	    rom = rooms[0]->start(Me);}catch(ROOM_ERR e){
	    catcher(e);
    }
	bool go = true;
 //////////////////////////////////////////////////////////////main game loop
	while(go){
		if(rom){
			try{
				rom = rom->start(Me);
			}catch(ROOM_ERR e){
				catcher(e);
			}
		}else{go=false;printf("SOME SORT OF POINTER ERROR\n");}
	}//end while
	return 0;
}
void enter(void){
    for(int i = 0; i<10;i++){
	delete rooms[i];
    }
	//delete [] tes;
	delete Me;
	cout<<"\nPress enter to continue...\n";
	//clearin();
	//usleep(10);
	cin.ignore(1,'\n');
	//system("pause");
}
void catcher(ROOM_ERR e){
	switch(e){
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
				mprintf("you died :(\n");
				mprintf("Game over\n");
				exit(0xDEAD);
		break;
		case ROOM_DONE:
				printf("you win!\n");
				exit(0xDEAD);
		break;
		case NO_ROOMS_ATTACHED:
				printf("You made it into a nightmare room with no exits!\n......Game over.....\n");
				exit(0xDEAD);
		break;
		case LOADED_RES:
		startup();
		try{
		rom = rooms[0]->start(Me);
		}catch(ROOM_ERR e){
			catcher(e);
		}
		break;
		}
}
void startup(){
rooms[0] = new room("You are in the room right outside of the locked train.\nAll around you can hear noises beyond imagination...");
rooms[1] = new room("You Enter a room with a big hole in the ground.\nUpon closer inspection you see that the hole is \nactually a well with something in it.");
    for (char i = 2; i<10;i++){rooms[i] = new room("RANDOM ROOM");}
    try{
	    rooms[0]->addper(&fred);
	    rooms[0]->attach(rooms[1],NORTH,true);
	    rooms[0]->attach(rooms[2],SOUTH,true);
	    rooms[0]->attach(rooms[3],WEST,true);
	    rooms[0]->attach(rooms[4],EAST,true);
	    for(char i=1;i<4;i++){
		    rooms[i]->addper(&tes[i-1]);
	    }
    }catch(ROOM_ERR e){
            catcher(e);
    }//end catch
}

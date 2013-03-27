// Zoel.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
//
ROOM_ERR dep;
room * rooms[10];
exitroom * exitr;
exitroom * conecter;
player * Me;
Weapon Sword;
zombie * tes[6];
room * rom = NULL;
int main(int argc, char* argv[]){
	atexit(enter);
	mprintf("Welcome to Zoel; a wonderful little Zork clone based on Joel\nLoad a previous character? y or any thing else for new game\n");
//	fflush(stdout);
	unsigned char te = 0;
	scanf("%c", &te);
	clearin();
	if(te == 'q'){exit(0);}
	    if(te == 'y'){
	    Me = new player(true);
	    mprintf("Enter a name then..\n");
	    char name[9];
	    scanf("%8s",name);
	    clearin();
	   try{
	    if(!(Me->load(name))){
		mprintf("Starting a new game then. you can try loading again once play starts\n");delete Me; Me = NULL; Me = new player();
	    }
	}catch(ROOM_ERR e){}
	}else{
	    Me = new player();
	    mprintf("You awake again in the train you were in when the cataclysm happened.\nYou check your pack and find that you have finally run out of food.\nYou've heard some very disturbing noises over the past couple days.\nThankfully you've been able to keep yourself hidden, rationing your food.\nYou grab your head as you stumble onto your feet, looks like its time to find\nsome food. You walk off the subway car and into the tunnel.\nThe door of the train closes behind you before finally losing power\n....seems like there's no hiding now....\n");
	    Sword.att = 4;
	    Sword.spd = 2;
	    strncpy(Sword.name,"Knife",sizeof("Knife"));
	    mprintf("You find your trusty knife still in your pack!\n");
	    Me->giveWep(Sword);
	}
	startup();
	    rom = rooms[9];
	bool go = true;
 //////////////////////////////////////////////////////////////main game loop
	while(go){
		if(rom){
			try{
				rom = rom->start(Me);
			}catch(ROOM_ERR e){
			    if(catcher(e)){go=false;}
			}
		}else{go=false;printf("SOME SORT OF POINTER ERROR\nBitch at andrew to fix!\n");}
	}//end while
	return 0;
}
void leave(){
    for(int i = 0; i<10;i++){
	delete rooms[i];
	rooms[i] = NULL;
    }
    delete exitr;
    exitr = NULL;
    for(char i = 0; i<6; i++){delete tes[i];tes[i]=NULL;}
}

void enter(void){
	leave();
	delete Me;
	cout<<"\nPress enter to continue...\n";
	cin.ignore(1,'\n');
}
bool catcher(ROOM_ERR e){
    switch(e){
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
		mainstreet();
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
			mprintf("you died :(\n");
			mprintf("Game over\n");
			exit(0xDEAD);
			break;
	case ROOM_DONE:
		     mprintf("You win!\nThanks for beta testing Zoel, I very much appreciate it :D\nYou can send errors to drew887 or post them on github.\nRemember to get the newest release ;D\n");
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
    FILE * pp = fopen("one","rb");
    char * tempdesc;
    if(!pp){printf("Corrupt or improper story file for the subway.\nPlease ask Andrew about this or redownload the story files\n");exit(0xDEAD);}
    unsigned int count = 0;
    dep = ROOM_DONE;
    for(char i = 0; i<6; i++){tes[i] = new zombie();}
    exitr = new exitroom(MAIN_STREET);
    for(int i = 0; i<10;i++){
	fread(&count,4,1,pp);
	if(feof(pp)){printf("Corrupt or improper story file for the subway. %d\nPlease ask Andrew about this or redownload the story files\n",i);exit(0xDEAD);}
	tempdesc = new char[count+1];
	fread(tempdesc,count,1,pp);
	tempdesc[count] = '\0';
	if(feof(pp)){printf("Corrupt or improper story file for the subway. %d\nPlease ask Andrew about this or redownload the story files\n",i);exit(0xDEAD);}
	if(i==5){
	 rooms[i] = new healroom(tempdesc);
	}else{
	rooms[i] = new room(tempdesc);
	}
	delete[] tempdesc;
	tempdesc = NULL;
	//printf("%s\n",tempdesc);
    }
    fclose(pp);
   // for (char i = 7; i<10;i++){rooms[i] = new room("RANDOM ROOM");}
	    //room0
	    rooms[0]->attach(rooms[1],NORTH,true);
	    rooms[0]->attach(rooms[2],WEST,true);
	    rooms[0]->attach(rooms[3],EAST,true);
	    //room1
	    //rooms[1]->attach(rooms[2],WEST,true);
	    rooms[1]->attach(rooms[4],EAST,true);
		rooms[1]->addper(tes[0]);
	    //room2
	    rooms[2]->attach(rooms[6],NORTH,true);
		rooms[2]->addper(tes[2]);
	    //room3
	    rooms[3]->attach(rooms[4],NORTH,true);
		rooms[3]->addper(tes[1]);
	    //room4
	    rooms[4]->attach(rooms[5],EAST,true);
	    //room5
	    rooms[5]->attach(rooms[8],NORTH);
		rooms[5]->addper(tes[3]);
	    //room6
	    rooms[6]->attach(rooms[7],WEST,true);
	    //room7
	    rooms[7]->attach(rooms[8],NORTH,true);
		rooms[7]->addper(tes[4]);
	    //rooms[8]
	    rooms[8]->attach(rooms[9],WEST,true);
	    rooms[8]->attach(rooms[5],EAST);
		rooms[8]->addper(tes[5]);
		//rooms[9]
	    rooms[9]->attach(exitr,WEST);
}

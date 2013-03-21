#include "stdafx.h"
#include "room.h"

room::room(const char * descr){
	percount = 0;
	attcount = 0;
	strcpy(desc,descr);
}
room::room(void){
	percount = 0;
	attcount = 0;
	desc[0] = 'a';
	desc[1] = '\0';
}

room* room::start(player * playera){
	printf("\t*****************\n%s\n\t*****************\n",desc);
	//mprintf(desc);
	if(attcount == 0){throw NO_ROOMS_ATTACHED; return NULL;}
	One = playera;
	room * next = NULL;
	bool vic = true;
	bool infi = true;
	bool chose = true;
	unsigned int numcheck =0;
	unsigned char te = 0;
   if(percount>0){
       printf("Oh no, %d enemies!\n",percount);
	while (vic){
		if(enimies[numcheck]->isalive){
		printf("******\nAn enemy %s is attacking!!\n******\n",enimies[numcheck]->classname);
		while(infi){
			printf("Enter a command!\n***a = attack r = run q = quit***\n");
			scanf("%c",&te);
			clearin();
			switch(te){
			case 'a':
				if(enimies[numcheck]->defend(playera)){
					infi = false;
				}else{enimies[numcheck]->attack(playera);}
			break;
			case 'r':
				printf("RUN\n");
                                infi = false;
                                vic = false;
                                break;
			break;
			case 'q':
				exit(0);
			break;
			default:
				printf("Unknown action?\n");
			}
                }//end while infi
		}else{mprintf("This ones dead!\n");}
		numcheck++;
		infi = true;
		if(numcheck == percount){vic=false;}
        }//end while vic
    }//end if percount
	while(chose){
		printf("Enter a command!\n***compass directions to move q to quit, h for help***\n");
		scanf("%c",&te);
		clearin();
		switch(te){
		case 'n': 
			next = getdir(NORTH);
			if(next ==NULL){printf("You can't go that way\n");}else{
				chose =false;
			}
		break;
		case 'S':
		playera->save();
		break;
		case 'L':
		char loaded[9];
		mprintf("Enter the name of a previous character\n");
		scanf("%8s",loaded);
		clearin();
		playera->load(loaded);
		return this;
		break;
                case 'l':
                printf("\t*****************\n%s\n\t*****************\n",desc);
                break;
		case 'e': 
			next = getdir(EAST);
			if(next ==NULL){printf("You can't go that way\n");}else{
				chose =false;
			}
		break;
		case 's': 
			next = getdir(SOUTH);
			if(next ==NULL){printf("You can't go that way\n");}else{
				chose =false;
			}
		break;
		case 'w': 
			next = getdir(WEST);
			if(next ==NULL){printf("You can't go that way\n");}else{
				chose =false;
			}
		break;
		case 'q':
			printf("Okay, exiting\n");
			exit(0);
		break;
		case 'h':
		mprintf("n\tgo north\ne\tgo east\ns\tgo south\nw\tgo west\nq\tquit\nl\tlook around\nS\tsave\nL\tload\n");
		break;
		default:
			mprintf("I dont know that command\n");
		}
	}
	return next;
}
bool room::addper(entity * person){
	if(percount < ROOM_MAX){
	enimies[percount] = person;
	percount++;
	}else{throw ROOM_FULL;return false;}
	return true;
}
bool room::attach(room * ar, room_dir direct){
	if(attcount >= 4){
		throw ALL_CON_USED;
		return false;
	}
	for(unsigned char i = 0;i<4;i++){
		if(attached.at_dir[i] == direct){
                        printf("CON %i\n",attached.at_dir[i]);throw CON_ALREADY_USED; return false;
		}
	}
        attached.attached[attcount] = ar;
	attached.at_dir[attcount] = direct;
	attcount++;
        return true;
}
room_dir swit(room_dir tw){
    switch(tw){
    case NORTH:
        return SOUTH;
    break;
    case SOUTH:
        return NORTH;
    break;
    case WEST:
        return EAST;
    break;
    case EAST:
        return WEST;
    break;
    }
}

bool room::attach(room * ar, room_dir direct,bool t){
        if(attcount >= 4){
                throw ALL_CON_USED;
                return false;
        }
        for(unsigned char i = 0;i<4;i++){
                if(attached.at_dir[i] == direct){
                        printf("CON %i\n",i);throw CON_ALREADY_USED; return false;
                }
        }
        attached.attached[attcount] = ar;
        attached.at_dir[attcount] = direct;
        attcount++;
        ar->attach(this,swit(direct));
        return true;
}
room::~room(void){
	
}

room * room::getdir(room_dir dir){
	room * temp = NULL;
	for(unsigned char i = 0; i<attcount;i++){
		if(attached.at_dir[i] == dir){
			temp = attached.attached[i];
			break;
		}
	}
	return temp;
}

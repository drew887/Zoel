#include "stdafx.h"
#include "player.h"
extern ROOM_ERR dep;
player::player(bool derp){
    inventory = new inven[3];
    inventory[0] = SHIRT;
    inventory[1] = CUFFS;
    inventory[2] = BOOTS;
}

player::player(void){
	printf("Hello there!\nWhat is your name?\n");
	scanf("%8s",classname);
	clearin();
	printf("So your name is %s?\nthat certainly is an...interesting name...\n",classname);
	srand( time(NULL) );
	hp = maxhp = (rand() % 8 )+ 30;
	srand( time(NULL) );
	def = (rand() % 3 )+ 1;
	srand( time(NULL) );
	att = (rand() % 3 )+ 1;
	printf("Well you have %d HP, %d def, and %d att\nGood luck!\n",hp,def,att);
	inventory = new inven[3];
	inventory[0] = SHIRT;
	inventory[1] = CUFFS;
	inventory[2] = BOOTS;
}

player::~player(void){
	delete [] inventory;
}

bool player::attack(entity * defender){
	if(defender == this){printf("I can't Attack myself!\n");return true;}
	return defender->defend(this);
}
bool player::defend(entity * attacker){
	if(attacker == this){printf("I can't Attack myself!\n");return true;}
	int temphp = hp;
	printf("%s is attacking!\t",attacker->classname);
	temphp -= (attacker->getatt() - def );
	if(temphp>=hp){
		printf("A MASSIVE 0 damage\t");
	}else{
	printf("A Whopping %d damage!\t",(hp-temphp));
	hp = temphp;
	}
	if(hp <=0){printf("%s has been defeated!\n",classname); isalive=false; throw DEAD_PLAYER; return true;}
	printf("%s has %dHP remaining!\n",classname,hp);
	return false;
}
void player::giveWep(Weapon wepa){
	wep = wepa;
}
unsigned int player::getatt(){
	return this->reatt();// + (rand() % wep.spd);
}
unsigned int player::reatt(){
    srand( time(NULL) );
   //printf("THIS %s %d ,%d\t",this->wep.name,(this->att + this->wep.att),this->wep.att);
    if(this->wep.spd == 0){return this->att + this->wep.att - 1;}
    return this->att + this->wep.att;// + (rand() % wep.spd);
}
//////////////////////////////////\\\\\\\\\\\\\\\\\>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
void player::save(){
FILE * pp = fopen(this->classname,"r");
unsigned char te =0;
    if(pp){
    mprintf("File already exsists. Overwrite? y/n\n");
    scanf("%c",&te);
    clearin();
	switch(te){
	case 'y':
	    mprintf("Overwriteing....\n");
	    break;
	default:
	    return;
	    break;
	}
	fclose(pp);
    }//end if pp
    pp = fopen(this->classname,"wb");
    if(!pp){printf("SOME SORT OF FILE IO ERROR, BITCH AT ANDREW TO FIX IT!\n"); return;}
	char check[] = "zoel";
	fwrite(check,sizeof(check),1,pp);
    fwrite(&att,sizeof(att),1,pp);
    fwrite(&def,sizeof(def),1,pp);
    fwrite(&maxhp,sizeof(maxhp),1,pp);
    fwrite(&hp,sizeof(hp),1,pp);
    fwrite(&wep,sizeof(Weapon),1,pp);
    fwrite(classname,sizeof(classname),1,pp);
    fwrite(&dep,sizeof(ROOM_ERR),1,pp);
    fclose(pp);
    printf("Save complete!\n");
}//end player::save/////////////////\\\\\\\\\\\\\\\\\\\\\\\\\\\>>>>>>>>>>>>>>>>>>>>>

bool player::load(const char *name){
    FILE * pp = fopen(name,"rb");
    if(!pp){mprintf("File not found, aborting load!\n"); return false;}
    char check[5];
    fread(check,5,1,pp);
    if(strncmp(check,"zoel",4)){mprintf("CORRUPT OR IMPROPERLY MODDED SAVE\n");return false;}
    fread(&att,sizeof(int),1,pp);
    fread(&def,sizeof(int),1,pp);
    fread(&maxhp,sizeof(int),1,pp);
    fread(&hp,sizeof(int),1,pp);
    fread(&this->wep,sizeof(Weapon),1,pp);
    fread(&classname,9,1,pp);
    fread(&dep,sizeof(ROOM_ERR),1,pp);
    printf("Loaded %s save!\n",this->classname);
    printf("Stats:\nMaxhp: %d\thp: %d\natt: %d\tdef: %d\n",maxhp,hp,att,def);
    fclose(pp);
    throw LOADED_RES;
    return true;
}

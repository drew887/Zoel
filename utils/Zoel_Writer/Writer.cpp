#include <iostream>
#include <string>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <cstring>


using namespace std;

struct Room{
    string desc;
    vector<int> connections;
    vector<char>directions;
};

vector<Room> rooms;
void addRoom();
void printRoom(Room room);
void readRoom();

class zoelMapVersion{
public:
    zoelMapVersion(char letter, char major, char minor){
        CUR_VER_LETTER = letter;
        CUR_VER_MAJOR = major;
        CUR_VER_MINOR = minor;
    }
    void print(){
        cout << "VERSION " << CUR_VER_LETTER << (int)CUR_VER_MAJOR << '.' << (int)CUR_VER_MINOR << endl;
    }
    void write(FILE * filePointer) const {
        fwrite(&CUR_VER_LETTER, 1, 1, filePointer);
        fwrite(&CUR_VER_MAJOR, 1, 1, filePointer);
        fwrite(&CUR_VER_MINOR, 1, 1, filePointer);
    }
    bool operator== (const zoelMapVersion & other){
        bool result = false;
        if(CUR_VER_LETTER == other.CUR_VER_LETTER){
            if(CUR_VER_MAJOR == other.CUR_VER_MAJOR){
                if(CUR_VER_MINOR == other.CUR_VER_MINOR){
                    result = true;
                }
            }
        }
        return result;
    }
    unsigned char CUR_VER_LETTER;
    unsigned char CUR_VER_MAJOR;
    unsigned char CUR_VER_MINOR;
};

const zoelMapVersion CUR_VER('c', 1, 0);

int main(int argc, char * argv[]){
    string songName = "";
    string mapName = "";
    bool loop = true;
    char te = 0;
    string commands = "a add room\ne erase all rooms!\np print room\nm add music\nr read in a zmap\nq quit\n";
    cout << commands << endl;
    while(loop){
        cout << "Enter state: ";
        cin >> te;
        cin.ignore(80, '\n');
        switch(te){
        case 'a':
            addRoom();
            break;
        case 'e':
            if(rooms.size() > 0){
                cout << "Remove all rooms?" << endl;
                char response = 0;
                while((response != 'y' && response != 'n') || cin.fail()){
                    cin.clear();
                    cout << "Please enter 'y' or 'n': ";
                    cin >> response;
                    cin.ignore(80, '\n');
                }
                if(response == 'y'){
                    rooms.clear();
                    cout << "Emptied!" << endl;
                }
            }
            else{
                cout << "No rooms to empty!" << endl;
            }
            break;
        case 'p':
            for(unsigned int room = 0; room < rooms.size(); room++){
                printRoom(rooms[room]);
            }
            break;
        case 'm':
            cout << endl << "Enter filename: ";
            getline(cin, songName);
            break;
        case 'r':
            readRoom();
            break;
        case 'q':
            loop = false;
            break;
        default:
            cout << commands << endl;
        }
    }
    string filename;
    cout << "Enter a filename (empty for no save): ";
    getline(cin, filename);
    if(filename.length() > 0){
        if(rooms.size() > 0){
            FILE * filePointer = fopen(filename.c_str(), "wb");
            if(filePointer){
                fwrite("ZMAP", 4, 1, filePointer);
                CUR_VER.write(filePointer);
                cout << "Enter Map name:" << endl;
                getline(cin, mapName);
                int mapNameLength = mapName.length();
                fwrite(&mapNameLength, sizeof(int), 1, filePointer);
                fwrite(mapName.c_str(), mapNameLength, 1, filePointer);
                int songLength = songName.length();
                if(songLength > 0){
                    fwrite("SONG", 4, 1, filePointer);
                    fwrite(&songLength, sizeof(int), 1, filePointer);
                    fwrite(songName.c_str(), songLength, 1, filePointer);
                }
                unsigned int numRooms = rooms.size();
                fwrite(&numRooms, sizeof(int), 1, filePointer);
                for(auto a : rooms){
                    fwrite("ROOM", 4, 1, filePointer);
                    int length = a.desc.length();
                    fwrite(&length, sizeof(int), 1, filePointer);
                    fwrite(a.desc.c_str(), a.desc.length(), 1, filePointer);
                    unsigned int conSize = a.connections.size();
                    fwrite(&conSize, sizeof(int), 1, filePointer);
                    for(unsigned int ctr = 0; ctr < conSize; ctr++){
                        fwrite(&a.connections[ctr], sizeof(int), 1, filePointer);
                        fwrite(&a.directions[ctr], sizeof(char), 1, filePointer);
                    }
                }
            }
            fwrite("END", 3, 1, filePointer);
            fclose(filePointer);
        }
        else
        {
            cout << endl << "ERROR WRITING, NO ROOMS WERE ADDED, FILE WON'T BE SAVED!\n\nPress enter to continue..." << endl << endl;
            cin.ignore(80, '\n');
            exit(-1);
        }
    }
    return 0;
}

void printRoom(Room room){
    cout << room.desc << endl;
    cout << "num cons: " << room.connections.size() << endl;
    for(unsigned int ctr = 0; ctr < room.connections.size(); ctr++){
        cout << room.connections[ctr] << room.directions[ctr] << " ";
    }
    cout << endl;
}

void readRoom(){
    string filename;
    string song = "";
    string name = "";
    cout << "Enter a filename: ";
    cin >> filename;
    FILE * filePointer = fopen(filename.c_str(), "rb");
    if(filePointer){
        char check[5] = {};
        fread(check, 4, 1, filePointer);
        if(!strncmp(check, "ZMAP", 4)){
            char ver[3] = {};
            fread(&ver, 3, 1, filePointer);
            zoelMapVersion version(ver[0], ver[1], ver[2]);
            cout << endl;
            version.print();
            unsigned int nameSize = 0;
            fread(&nameSize, sizeof(int), 1, filePointer);
            char * cname = new char[nameSize + 1];
            cname[nameSize] = 0;
            fread(cname, nameSize, 1, filePointer);
            name = cname;
            delete[] cname;
            cout << "Map name: " << name << endl;
            fread(check, 4, 1, filePointer);
            if(!strncmp(check, "SONG", 4)){
                unsigned int songLength = 0;
                fread(&songLength, sizeof(int), 1, filePointer);
                char * songName = new char[songLength + 1];
                songName[songLength] = 0;
                fread(songName, songLength, 1, filePointer);
                song = songName;
                delete[] songName;
            }
            else{
                fseek(filePointer, -4, SEEK_CUR);
            }
            unsigned int numRooms = 0;
            fread(&numRooms, sizeof(int), 1, filePointer);
            for(unsigned int loop = 0; loop < numRooms; loop++){
                fread(check, 4, 1, filePointer);
                if(!strncmp(check, "ROOM", 4)){
                    Room room;
                    unsigned int descLength = 0;
                    fread(&descLength, sizeof(int), 1, filePointer);
                    char * tDesc = new char[descLength + 1];
                    tDesc[descLength] = 0;
                    fread(tDesc, descLength, 1, filePointer);
                    room.desc = tDesc;
                    delete[] tDesc;
                    unsigned int roomCount = 0;
                    fread(&roomCount, sizeof(int), 1, filePointer);
                    for(unsigned int ctr = 0; ctr < roomCount; ctr++){
                        unsigned int num = 0;
                        char dir = 'N';
                        fread(&num, sizeof(int), 1, filePointer);
                        fread(&dir, sizeof(char), 1, filePointer);
                        room.connections.push_back(num);
                        room.directions.push_back(dir);
                    }
                    printRoom(room);
                }
                else{
                    cout << "ERR READING ROOM" << endl;
                }
            }
            if(song.length() > 0){
                cout << "Song name: " << song << endl;
            }
        }
        else{
            cout << "File is not a valid ZMAP" << endl;
        }
        fclose(filePointer);
    }
    else{
        cout << "File not found!" << endl;
    }
}

void addRoom(){
    Room room;
    cout << "Enter Description of room: " << endl;
    getline(cin, room.desc);
    int input = 0;
    int curCon = 0;
    bool loop = true;
    char command;
    string commands = "\na to add a connection\np to print the current room info\nr to reset the current room\nq to finish editing the room\n";
    cout << commands << endl;
    while(loop){
        cout << "Enter command: ";
        cin >> command;
        cin.ignore(80, '\n');
        switch(command){
        case 'a':
            if(curCon < 4){
                cout << "Enter connection number: ";
                cin >> input;
                while(cin.fail()){
                    cin.clear();
                    cin.ignore(80, '\n');
                    cout << "Please enter only positive numbers: ";
                    cin >> input;
                }
                if(input < 0){
                    break;
                }
                room.connections.push_back(input);
                char dir = 0;
                cout << "Enter the direction it lies: ";
                cin >> dir;
                bool loop = true;
                while(loop){
                    switch(dir){
                    case 'N':
                    case 'E':
                    case 'S':
                    case 'W':
                        room.directions.push_back(dir);
                        loop = false;
                        break;
                    default:
                        cout << "Please enter N, S, W, or E: ";
                        cin.ignore(80, '\n');
                        cin >> dir;
                    }
                }
            }
            else{
                cout << "Already filled all 4 connections!" << endl;
            }
            curCon++;
            break;
        case 'p':
            printRoom(room);
            break;
        case 'r':
            room.connections.clear();
            room.directions.clear();
            cout << "Enter description of room" << endl;
            getline(cin, room.desc);
            break;
        case 'q':
            loop = false;
            break;
        default:
            cout << commands << endl;
            break;
        }//end switch(command)
    }
    rooms.push_back(room);

}

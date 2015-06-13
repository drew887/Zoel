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

int main(int argc, char * argv[]){

	bool loop = true;
	char te = 0;
	while (loop){
		cout << "Enter state: ";
		cin >> te;
		switch (te){
		case 'a':
			addRoom();
			break;
		case 'p':
			if (rooms.size() > 0){
				printRoom(rooms[0]);
			}
			break;
		case 'r':
			readRoom();
			break;
		case 'q':
			loop = false;
			break;
		default:
			cout << "I dont know " << te << endl;
		}
	}
	string filename;
	cout << "Enter a filename: ";
	cin >> filename;
	FILE * filePointer = fopen(filename.c_str(), "wb");
	if (filePointer){
		fwrite("ZMAP", 4, 1, filePointer);
		unsigned int numRooms = rooms.size();
		fwrite(&numRooms, sizeof(int), 1, filePointer);
		for (auto a : rooms){
			fwrite("ROOM", 4, 1, filePointer);
			int length = a.desc.length();
			fwrite(&length, sizeof(int), 1, filePointer);
			fwrite(a.desc.c_str(), a.desc.length(), 1, filePointer);
			unsigned int conSize = a.connections.size();
			fwrite(&conSize, sizeof(int), 1, filePointer);
			for (unsigned int ctr = 0; ctr < conSize; ctr++){
				fwrite(&a.connections[ctr], sizeof(int), 1, filePointer);
				fwrite(&a.directions[ctr], sizeof(char), 1, filePointer);
			}
		}
		fwrite("END", 3, 1, filePointer);
		fclose(filePointer);
	}
	return 0;
}

void printRoom(Room room){
	cout << room.desc << endl;
	cout << "num cons: " << room.connections.size() << endl;
	for (unsigned int ctr = 0; ctr < room.connections.size(); ctr++){
		cout << room.connections[ctr] << room.directions[ctr] << " ";
	}
	cout << endl;
}

void readRoom(){
	string filename;
	cout << "Enter a filename: ";
	cin >> filename;
	FILE * filePointer = fopen(filename.c_str(), "rb");
	if (filePointer){
		char check[5] = {};
		fread(check, 4, 1, filePointer);
		if (!strncmp(check, "ZMAP", 4)){
			unsigned int numRooms = 0;
			fread(&numRooms, sizeof(int), 1, filePointer);
			for (unsigned int loop = 0; loop < numRooms; loop++){
				fread(check, 4, 1, filePointer);
				if (!strncmp(check, "ROOM", 4)){
					Room room;
					unsigned int descLength = 0;
					fread(&descLength, sizeof(int), 1, filePointer);
					char * tDesc = new char[descLength + 1];
					tDesc[descLength] = 0;
					fread(tDesc, descLength, 1, filePointer);
					room.desc = tDesc;
					delete [] tDesc;
					unsigned int roomCount = 0;
					fread(&roomCount, sizeof(int), 1, filePointer);
					for (unsigned int ctr = 0; ctr < roomCount; ctr++){
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
	cin.ignore(80, '\n');
	getline(cin, room.desc);
	int input = 0;
	int curCon = 0;
	while (curCon < 4){
		cout << "Enter connection number (-1 to quit): ";
		cin >> input;
		while (cin.fail()){
			cin.clear();
			cin.ignore(80, '\n');
			cout << "Please enter only positive numbers or any negative to quit: ";
			cin >> input;
		}
		if (input < 0){
			break;
		}
		room.connections.push_back(input);
		char dir = 0;
		cout << "Enter the direction it lies: ";
		cin >> dir;
		bool loop = true;
		while (loop){
			switch (dir){
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
		curCon++;
	}
	rooms.push_back(room);

}

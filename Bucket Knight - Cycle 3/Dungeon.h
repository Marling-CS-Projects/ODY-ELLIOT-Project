#pragma once
#include "Level.h"
#include <vector>
#include <cstdlib>

using namespace std;

class Dungeon
{

public:
	Dungeon();
	Dungeon(int numRooms);
	~Dungeon();

	vector<string> GetRooms();
	void GenerateLayout();
	void DrawCurrentRoom();

	int numRooms;
	vector<string> rooms{};
	//vector<int> currentLayout{};
	vector<Level*> currentLayout;
	int currentRoom;
};


#pragma once
#include "Level.h"
#include <vector>
#include <cstdlib>

#include <iostream>
#include "SDL.h"

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
	vector<Level*> currentLayout;
	int currentRoom;
};


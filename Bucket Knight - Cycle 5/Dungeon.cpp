#include "Dungeon.h"
#include <iostream>

Dungeon::Dungeon()
{
	this->numRooms = 5;
	this->rooms = GetRooms();
	this->currentRoom = 0;
}

Dungeon::Dungeon(int numRooms)
{
	this->numRooms = numRooms;
	this->rooms = GetRooms();
	this->currentRoom = 0;
}

void Dungeon::GenerateLayout()
{
	this->currentLayout = {};
	currentLayout.resize(numRooms);

	currentLayout[0] = new Level("RoomSTART", 1); // adds the start room
	currentLayout[0]->tag = "start";

	std::srand(time(NULL));

	for (int i = 0; i < numRooms - 2; i++)
	{
		currentLayout[i + 1] = new Level(rooms[(std::rand() % (this->rooms.size() - 2)) + 2], 2);
		currentLayout[i + 1]->tag = "room";
	}

	currentLayout[numRooms-1] = new Level("RoomEND", 1); // adds the end room
	currentLayout[numRooms-1]->tag = "end";
}

void Dungeon::DrawCurrentRoom()
{
	if (currentRoom < 0) { currentRoom = 0; }
	else if (currentRoom > currentLayout.size() - 1) { currentRoom = currentLayout.size() - 1; }
	currentLayout.at(currentRoom)->BuildLevel();
}
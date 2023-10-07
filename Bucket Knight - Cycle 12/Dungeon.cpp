#include "Dungeon.h"
#include <iostream>

Dungeon::Dungeon()
{
	this->numRooms = 5;
	this->rooms = GetRooms();
	this->currentRoom = 0;
	this->currentLayout = {};

	this->enemyNumber = 1;
}

Dungeon::Dungeon(int numRooms)
{
	this->numRooms = numRooms;
	this->rooms = GetRooms();
	this->currentRoom = 0;
	this->currentLayout = {};

	this->enemyNumber = 1;
}

void Dungeon::GenerateLayout()
{
	currentLayout.resize(numRooms);

	currentLayout[0] = new Level("RoomSTART", enemyNumber); // adds the start room
	currentLayout[0]->tag = "start";

	std::srand(time(NULL));

	for (int i = 0; i < numRooms - 2; i++)
	{
		if (i < 1)
		{
			enemyNumber = 1;
		}
		else if (i % 2 == 0)
		{
			enemyNumber = i / 2;
		}
		else
		{
			enemyNumber = (i + 1) / 2;
		}

		if (enemyNumber > 10)
		{
			enemyNumber = 10;
		}

		currentLayout[i + 1] = new Level(rooms[(std::rand() % (this->rooms.size() - 2)) + 2], enemyNumber);
		currentLayout[i + 1]->tag = "room";
	}

	currentLayout[numRooms-1] = new Level("RoomEND", enemyNumber + 1); // adds the end room
	currentLayout[numRooms-1]->tag = "end";
}

void Dungeon::DrawCurrentRoom()
{
	if (currentRoom <= 0) { currentRoom = 0; }
	else if (currentRoom >= currentLayout.size() - 1) { currentRoom = currentLayout.size() - 1; }
	this->currentLayout.at(currentRoom)->BuildLevel();
}
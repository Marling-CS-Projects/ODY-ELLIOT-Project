#include "Level.h"
#include <iostream>

Level::Level(std::string lvlName, int e)
{
	SetVariables(lvlName, "room", 16, 16, e);
}

Level::Level(std::string lvlName, int x, int y, int e)
{
	SetVariables(lvlName, "room", x, y, e);
}

Level::~Level()
{
	
}

void Level::SetVariables(std::string lvlName, std::string tag, int x, int y, int numEnemies)
{
	this->lvlName = lvlName;
	this->x = x;
	this->y = x;
	this->tag = tag;
	this->numberOfEnemies = numEnemies;
}
#include "Level.h"
#include <iostream>

Level::Level(std::string lvlName)
{
	SetVariables(lvlName, "room", 16, 16);
}

Level::Level(std::string lvlName, int x, int y)
{
	SetVariables(lvlName, "room", x, y);
}

Level::~Level()
{
	
}

void Level::SetVariables(std::string lvlName, std::string tag, int x, int y)
{
	this->lvlName = lvlName;
	this->x = x;
	this->y = x;
	this->tag = tag;
}
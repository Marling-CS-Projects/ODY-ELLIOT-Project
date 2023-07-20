#pragma once
#include "TileMap.h"
#include <string>

class Level
{

public:
	Level(std::string lvlName);
	Level(std::string lvlName, int x, int y);
	~Level();

	void SetVariables(std::string lvlName, std::string tag, int x, int y);

	void BuildLevel();

	int x;
	int y;
	std::string lvlName;
	std::string tag;

};


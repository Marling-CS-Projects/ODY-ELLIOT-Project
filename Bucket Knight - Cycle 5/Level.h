#pragma once
#include "Objects.h"
#include "TileMap.h"
#include <string>

class Level
{

public:
	Level(std::string lvlName, int enemies);
	Level(std::string lvlName, int x, int y, int enemies);
	~Level();

	void SetVariables(std::string lvlName, std::string tag, int x, int y, int numEnemies);

	void BuildLevel();
	void SpawnEnemies();

	int x;
	int y;
	int numberOfEnemies;
	std::string lvlName;
	std::string tag;

};


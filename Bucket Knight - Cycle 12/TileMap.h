#pragma once
#include <string>
#include <ios>
#include <fstream>
#include <stdlib.h>

class TileMap
{

public:
	TileMap();
	~TileMap();

	static void LoadTiles(std::string path, int sizeX, int sizeY);
	
};


#pragma once
#include <string>

class TileMap
{

public:
	TileMap();
	~TileMap();

	static void LoadTiles(std::string path, int sizeX, int sizeY);
	
};


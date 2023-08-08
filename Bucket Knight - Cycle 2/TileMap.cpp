#include "TileMap.h"
#include "Game.h"
#include <fstream>

TileMap::TileMap()
{

}

TileMap::~TileMap()
{
	
}

void TileMap::LoadTiles(std::string path, int sizeX, int sizeY)
{
	char tile;
	std::fstream tilemapFile;
	tilemapFile.open(path);

	for (int y = 0; y < sizeY; y++)
	{
		for (int x = 0; x < sizeX; x++)
		{
			tilemapFile.get(tile);
			Game::AddTile(atoi(&tile), x * 24, y * 24);
			tilemapFile.ignore();
		}
	}

	tilemapFile.close();
}
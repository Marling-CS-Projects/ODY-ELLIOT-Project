# 2.2.2 Cycle 2

## Design

### Objectives

In this cycle I aim to:

* [x] Create a tile-map system
* [x] Create a wall with collision
* [x] Add appropriate render layers

### Usability Features

### Key Variables

| Variable Name | Use                                            |
| ------------- | ---------------------------------------------- |
| tiles         | stores all the entities in the 'tilemap' group |
| players       | stores all the entities in the 'players' group |
| enemies       | stores all the entities in the 'enemies' group |

### Pseudocode

{% code title="TileMap.cpp" %}
```cpp
tilemap = OpenFile("tiles.txt")
tileType1 = OpenFile("tile1texture.png") // represented by a 0
tileType2 = OpenFile("tile2texture.png") // represented by a 1

void LoadTiles(tilemap){
    for (tile in tilemap)
    {
        if (tile == 0)
        {
            newtile = createTile(tileType1)
        }
        else if (tile == 1)
        {
            newtile = createTile(tyleType2)
        }
        // I could also use a switch statement to achieve the same effect
        
        newTile.addToGroup(tiles) // stores all the tiles to render
    }
}
```
{% endcode %}

Using this system I can create a tilemap system that imports an external text file to quickly make tilemaps appear in the game.

{% code title="Collisions.cpp" %}
```cpp
bool isColliding(hitbox1, hitbox2) // uses AABB collision detection
{
    if (
    rectA.x + rectA.w >= rectB.x &&
    rectB.x + rectB.w >= rectA.x &&
    rectA.y + rectA.h >= rectB.y &&
    rectB.y + rectB.h >= rectA.y
    )
    {
        return true
    }
    else
    {
        return false
    }
}
```
{% endcode %}

If the `player` is colliding with the `wall` then `isColliding(player.hitbox, wall.hitbox)` will return `true`.

{% code title="Game.cpp" %}
```cpp
// this is an extract of the Game.cpp file

void render()
{
    tiles->draw()
    players->draw()
    enemies->draw()
}
```
{% endcode %}

Draws each layer in order in order for the player and enemies to be displayed above the tilemap.

## Development

### Outcome

{% code title="Tilemap.cpp" %}
```cpp
#include "TileMap.h"
#include "Game.h"
#include <fstream>

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
```
{% endcode %}

LoadTiles() loads the tilemap from an external file path and requests the size of the tilemap in order to display in properly. This function is called in Game.cpp and the relevant information is passed through.

You can find the rest of the solution [here](https://github.com/Marling-CS-Projects/ODY-ELLIOT-Project/tree/cycles/Bucket%20Knight%20-%20Cycle%202).

### Challenges

The main challenges was creating the tilemap system where you can use external files to create an array of tiles.

## Testing

Evidence for testing

### Tests

<table><thead><tr><th width="90">Test</th><th width="141">Instructions</th><th>What I expect</th><th width="163">What actually happens</th><th>Pass/Fail</th></tr></thead><tbody><tr><td>1</td><td>Run code</td><td>Black Re-sizable Window is opened</td><td>As expected</td><td>Pass</td></tr><tr><td>2</td><td>Press buttons</td><td>Something happens</td><td>As expected</td><td>Pass</td></tr></tbody></table>

### Evidence

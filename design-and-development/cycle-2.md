# 2.2.2 Cycle 2

## Design

### Objectives

In this cycle I aim to:

* [x] Create a tile-map system
* [x] Create a wall with collision detection
* [x] Add appropriate render layers

### Usability Features



### Key Variables

| Variable Name | Use                                            |
| ------------- | ---------------------------------------------- |
| tiles         | stores all the entities in the 'tilemap' group |
| players       | stores all the entities in the 'players' group |
| enemies       | stores all the entities in the 'enemies' group |

### Pseudocode

{% code title="Tile Map" %}
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

{% code title="Check Collisions" %}
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

{% code title="Game Loop" %}
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

`LoadTiles()` loads the tilemap from an external file path and requests the size of the tilemap in order to display in properly. This function is called in `Game.cpp` and the relevant information is passed through.

{% code title="Collision.cpp" %}
```cpp
#include "Collision.h"
#include "ColliderComponent.h"

bool Collision::AABB(const SDL_Rect& rectA, const SDL_Rect& rectB)
{

	if (
		rectA.x + rectA.w >= rectB.x &&
		rectB.x + rectB.w >= rectA.x &&
		rectA.y + rectA.h >= rectB.y &&
		rectB.y + rectB.h >= rectA.y
		)
	{
		return true;
	}

	return false;
}

// ColliderComponent& is a reference to the entity's collider component
bool Collision::AABB(const ColliderComponent& colA, const ColliderComponent& colB)
{
	if (AABB(colA.collider, colB.collider) && colA.tag != colB.tag)
	{
		std::cout << colA.tag << " hit " << colB.tag << std::endl;
		return true;
	}

	return false;
}
```
{% endcode %}

My game uses AABB collision detection which detects whether or not entities are overlapping. In the solution above, there are two ways to call the method to detect collision (I use the second method much more frequently as it is easier to pass in the collider component reference than the `SDL_Rect`.

The collider component also has a tag to tell what has hit what.&#x20;

You can find the rest of the solution [here](https://github.com/Marling-CS-Projects/ODY-ELLIOT-Project/tree/cycles/Bucket%20Knight%20-%20Cycle%202).

### Challenges

The main challenges was creating the tilemap system where you can use external files to create an array of tiles that will be displayed to the user.

## Testing

<table><thead><tr><th width="90">Test</th><th width="141">Instructions</th><th>What I expect</th><th width="163">What actually happens</th><th>Pass/Fail</th></tr></thead><tbody><tr><td>1</td><td>Run code</td><td>Tiles are in the shape of a smiley face.</td><td>All tiles were jumbled.</td><td>Fail</td></tr><tr><td>2</td><td>Run code</td><td>Tiles are in the shape of a smiley face.</td><td>As expected</td><td>Pass</td></tr><tr><td>3</td><td>Move the player into the wall</td><td>A console log stating there has been a collision between the player and the wall.</td><td>As expected</td><td>Pass</td></tr></tbody></table>

### Evidence

<figure><img src="../.gitbook/assets/Screenshot 2023-06-15 093249.png" alt=""><figcaption><p>A screenshot of the console and the game before the player collides with the wall</p></figcaption></figure>

Before the player collides with the wall there is no collision log in the console.

<figure><img src="../.gitbook/assets/image (18).png" alt=""><figcaption><p>A screenshot of the console and the game afterthe player collides with the wall</p></figcaption></figure>

After the player collided with the wall, however, there is a collision log in the console which demonstrates the collision detection works.

As well as that, the tilemap (imported from an external file) clearly prints a smiley face which proves the tilemap system works.

{% embed url="https://youtu.be/-B1UMLdatTE" %}
The video above shows the second cycle of my game ([https://youtu.be/-B1UMLdatTE](https://youtu.be/-B1UMLdatTE))
{% endembed %}

The YouTube video (shown above) demonstrates render correct render layering as the player is displayed on top of the tiles. However, the player shouldn't be above the wall but that is due to me grouping the wall object with tile objects temporarily while the wall has no collision.

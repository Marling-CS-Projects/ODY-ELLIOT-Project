# 2.2.2 Cycle 2

{% hint style="danger" %}
Most of the code added in this cycle was created by Let's Make Games on YouTube ([https://www.youtube.com/@CarlBirch](https://www.youtube.com/@CarlBirch)). The tutorials he created helped me learn C++ and SDL2 so I could go on to later create the rest of the game.
{% endhint %}

## Design

Cycle 2 revolves around the game's tile system which will work by accessing external '.txt' files and then creating a tile map using the external files and the tile set.

An example of what may be in the external file is shown below where the 0s and 1s correspond to different tiles, to be rendered, from the tile set.

<figure><img src="../.gitbook/assets/image (2) (1) (1) (1).png" alt="" width="504"><figcaption><p>This tile-map is of a 'Smiley-Face'</p></figcaption></figure>

### Objectives

In this cycle, I aim to:

* [x] Create a tile-map system
* [x] Create a wall with collision detection
* [x] Add appropriate render layers

### Usability Features

Render Groups/Layers - The player's group will be rendered above the tiles group in order for the user to be aware of where they are in the scene.

### Pseudocode

{% code title="Tile Map" %}
```cpp
// Load the tilemap from a text file
tilemap = OpenFile("tiles.txt");

// Load textures for tile types
tileType1 = OpenFile("tile1texture.png"); // Represented by a 0 in the tilemap
tileType2 = OpenFile("tile2texture.png"); // Represented by a 1 in the tilemap

// Function to load tiles from the tilemap
void LoadTiles(tilemap)
{
    for (tile in tilemap)
    {
        if (tile == 0)
        {
            // Create a new tile using tileType1 texture
            newTile = createTile(tileType1);
        }
        else if (tile == 1)
        {
            // Create a new tile using tileType2 texture
            newTile = createTile(tileType2);
        }
        
        // Add the new tile to a group (e.g., 'tiles') for rendering
        newTile.addToGroup(tiles);
    }
}
```
{% endcode %}

Using this system I can create a tilemap system that imports an external text file to quickly make tilemaps appear in the game.

{% code title="Check Collisions" %}
```cpp
function isColliding(hitbox1, hitbox2):
    // Check if there is a collision between hitbox1 and hitbox2 using AABB collision detection
    
    // Check if the right edge of hitbox1 is to the right of the left edge of hitbox2
    if (hitbox1.x + hitbox1.width >= hitbox2.x) and
    // Check if the right edge of hitbox2 is to the right of the left edge of hitbox1
       (hitbox2.x + hitbox2.width >= hitbox1.x) and
    // Check if the bottom edge of hitbox1 is below the top edge of hitbox2
       (hitbox1.y + hitbox1.height >= hitbox2.y) and
    // Check if the bottom edge of hitbox2 is below the top edge of hitbox1
       (hitbox2.y + hitbox2.height >= hitbox1.y):
       
        return true  // Collision detected
    
    return false  // No collision detected
```
{% endcode %}

If the `player` is colliding with the `wall` then `isColliding(player.hitbox, wall.hitbox)` will return `true`. This function uses AABB collision detection.

{% code title="Game Loop" %}
```cpp
function render():
    // Render tiles
    tiles.draw()
    
    // Render players
    players.draw()
    
    // Render enemies
    enemies.draw()
```
{% endcode %}

Draws each layer in order in order for the player and enemies to be displayed above the tilemap.

## Development

### Outcome

{% code title="Tilemap" %}
```cpp
#include "TileMap.h"
#include "Game.h"
#include <fstream>

void TileMap::LoadTiles(std::string path, int sizeX, int sizeY)
{
    char tile; // Variable to store each character read from the file
    std::fstream tilemapFile; // File stream for reading the tilemap file
    tilemapFile.open(path); // Open the tilemap file

    for (int y = 0; y < sizeY; y++)
    {
        for (int x = 0; x < sizeX; x++)
        {
            tilemapFile.get(tile); // Read a character from the file

            // Add a tile to the game based on the character read and the current position
            Game::AddTile(atoi(&tile), x * 24, y * 24);

            tilemapFile.ignore(); // Ignore any extra characters (e.g., newline)
        }
    }

    tilemapFile.close(); // Close the tilemap file after reading
}
```
{% endcode %}

`LoadTiles()` loads the tilemap from an external file path and requests the size of the tilemap in order to display it properly. This function is called in `Game.cpp` and the relevant information is passed through.

{% code title="Collision Functions" %}
```cpp
#include "Collision.h"
#include "ColliderComponent.h"

// Checks for AABB (Axis-Aligned Bounding Box) collision between two SDL_Rects.
bool Collision::AABB(const SDL_Rect& rectA, const SDL_Rect& rectB)
{
    // Check if the two rectangles overlap in both the X and Y axes.
    if (rectA.x + rectA.w >= rectB.x &&
        rectB.x + rectB.w >= rectA.x &&
        rectA.y + rectA.h >= rectB.y &&
        rectB.y + rectB.h >= rectA.y)
    {
        return true; // Collision detected.
    }

    return false; // No collision.
}

// Checks for AABB collision between two ColliderComponents.
// colA and colB are references to the entity's collider components.
bool Collision::AABB(const ColliderComponent& colA, const ColliderComponent& colB)
{
    // Use the AABB function to check collision between the colliders' rectangles.
    if (AABB(colA.collider, colB.collider) && colA.tag != colB.tag)
    {
        std::cout << colA.tag << " hit " << colB.tag << std::endl;
        return true; // Collision detected between different tags.
    }

    return false; // No collision or collision between the same tags.
}
```
{% endcode %}

My game uses AABB collision detection which detects whether or not entities are overlapping. In the solution above, there are two ways to call the method to detect collision (I use the second method much more frequently as it is easier to pass in the collider component reference than the `SDL_Rect`.

The collider component also has a tag to tell what has hit what.&#x20;

You can find the rest of the solution [here](https://github.com/Marling-CS-Projects/ODY-ELLIOT-Project/tree/cycles/Bucket%20Knight%20-%20Cycle%202).

### Challenges

The main challenge was creating the tilemap system where you can use external files to create an array of tiles that will be displayed to the user.

## Testing

<table><thead><tr><th width="90">Test</th><th width="141">Instructions</th><th>What I expect</th><th width="163">What actually happens</th><th>Pass/Fail</th></tr></thead><tbody><tr><td>1</td><td>Run code</td><td>Tiles are in the shape of a smiley face.</td><td>All tiles were jumbled.</td><td>Fail</td></tr><tr><td>2</td><td>Run code</td><td>Tiles are in the shape of a smiley face.</td><td>As expected</td><td>Pass</td></tr><tr><td>3</td><td>Move the player into the wall</td><td>A console log stating there has been a collision between the player and the wall.</td><td>As expected</td><td>Pass</td></tr></tbody></table>

### Evidence

<figure><img src="../.gitbook/assets/Screenshot 2023-06-15 093249.png" alt=""><figcaption><p>A screenshot of the console and the game before the player collides with the wall</p></figcaption></figure>

Before the player collides with the wall there is no collision log in the console.

<figure><img src="../.gitbook/assets/image (18).png" alt=""><figcaption><p>A screenshot of the console and the game afterthe player collides with the wall</p></figcaption></figure>

After the player collides with the wall, however, there is a collision log in the console which demonstrates the collision detection works.

As well as that, the tilemap (imported from an external file) clearly prints a smiley face which proves the tilemap system works.

{% embed url="https://youtu.be/-B1UMLdatTE" %}
The video above shows the second cycle of my game ([https://youtu.be/-B1UMLdatTE](https://youtu.be/-B1UMLdatTE))
{% endembed %}

The YouTube video (shown above) demonstrates correct render layering as the player is displayed on top of the tiles. However, the player shouldn't be above the wall but that is due to me grouping the wall object with tile objects temporarily while the wall has no collision.

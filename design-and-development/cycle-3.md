# 2.2.3 Cycle 3

## Design

This cycle is about creating the dungeon generator which will create the dungeon layout the player has to play through.

In this cycle, I have also added some quality-of-life features for development such as a new `Object` class to make it easier to create entities.

As well as that, I added viewport scaling so the user can play the game at any window size.

### Objectives

In this cycle, I aim to:

* [x] Create a Dungeon Layout Generator
* [x] Have each room connect to each other
* [x] New Level Creation System
* [x] Dungeon Walls with Collision
* [x] Streamlined Entity Creation System
* [x] Viewport Scaling

### Usability Features

Viewport Scaling - This allows the user to play the game at any window size.

### Key Variables

<table><thead><tr><th width="303">Variable Name</th><th>Use</th></tr></thead><tbody><tr><td>currentRoom</td><td>stores the room the player is currently in</td></tr><tr><td>numRooms</td><td>stores how many rooms the dungeon will have</td></tr><tr><td>currentLayout</td><td>stores the current layout of the entire dungeon (the sequence of rooms the player must progress through)</td></tr></tbody></table>

### Pseudocode

{% code title="Dungeon Creator" %}
```cpp
// Dungeon class constructor
Dungeon(numRooms):
    // Initialize number of rooms
    this->numRooms = numRooms
    // Get names of room files
    this->rooms = GetRooms()
    // Set current room to start
    this->currentRoom = 0

// Function to get room file names
vector<string> GetRooms():
    // Return a list of room file names
    return vector<string>
    {
        "Room1.txt",
        "Room2.txt",
        "Room3.txt"
    }

// Function to generate the dungeon layout
GenerateLayout():
    // Initialize the current layout
    this->currentLayout = {}
    // Set the size of the layout
    currentLayout.size() = numRooms
    
    // Add the start room
    currentLayout.start() = new Level("RoomSTART")

    // Generate rooms between start and end
    for i from 0 to numRooms - 2:
        // Generate a random index for selecting a room file
        randomIndex = std::rand() % (this->rooms.size() - 2) + 2
        // Create a new level using the selected room file
        currentLayout[i + 1] = new Level(rooms[randomIndex])

    // Add the end room
    currentLayout.end() = new Level("RoomEND")

// Function to draw the current room
DrawCurrentRoom():
    // Ensure the current room index is within bounds
    if currentRoom < 0:
        currentRoom = 0
    else if currentRoom > currentLayout.size() - 1:
        currentRoom = currentLayout.size() - 1
    // Build and display the current room
    currentLayout.at(currentRoom)->BuildLevel()

// Class members
int numRooms
vector<string> rooms{}
vector<Level*> currentLayout
int currentRoom
```
{% endcode %}

The dungeon generator will be created as an entity and will render the current level the player is in.

## Development

### Outcome

{% code title="Dungeon Class Definitions" %}
```cpp
#include "Dungeon.h"
#include <iostream>

Dungeon::Dungeon()
{
    // Initialize with a default number of rooms
    this->numRooms = 5;
    this->rooms = GetRooms(); // Get available room types
    this->currentRoom = 0; // Initialize the current room index
}

Dungeon::Dungeon(int numRooms)
{
    // Initialize with a specified number of rooms
    this->numRooms = numRooms;
    this->rooms = GetRooms(); // Get available room types
    this->currentRoom = 0; // Initialize the current room index
}

void Dungeon::GenerateLayout()
{
    this->currentLayout = {};
    currentLayout.resize(numRooms); // Resize the layout container to hold room pointers

    currentLayout[0] = new Level("RoomSTART"); // Add the start room as the first room
    currentLayout[0]->tag = "start"; // Assign a tag to the start room

    std::srand(time(NULL)); // Seed the random number generator

    for (int i = 0; i < numRooms - 2; i++)
    {
        // Add random rooms to the layout based on available room types
        currentLayout[i + 1] = new Level(rooms[(std::rand() % (this->rooms.size() - 2)) + 2]);
        currentLayout[i + 1]->tag = "room"; // Assign a tag to regular rooms
    }

    currentLayout[numRooms - 1] = new Level("RoomEND"); // Add the end room as the last room
    currentLayout[numRooms - 1]->tag = "end"; // Assign a tag to the end room
}

void Dungeon::DrawCurrentRoom()
{
    if (currentRoom < 0) { currentRoom = 0; } // Ensure the current room index is not negative
    else if (currentRoom > currentLayout.size() - 1) { currentRoom = currentLayout.size() - 1; } // Ensure the current room index is within bounds

    currentLayout.at(currentRoom)->BuildLevel(); // Build and draw the current room
}
```
{% endcode %}

{% code title="Level Class Definitions" %}
```cpp
#include "Level.h"
#include <iostream>

Level::Level(std::string lvlName)
{
    // Constructor that initializes the level with default tag and dimensions
    SetVariables(lvlName, "room", 16, 16);
}

Level::Level(std::string lvlName, int x, int y)
{
    // Constructor that initializes the level with specified tag and dimensions
    SetVariables(lvlName, "room", x, y);
}

Level::~Level()
{
    // Destructor - Currently no additional cleanup is needed
}

void Level::SetVariables(std::string lvlName, std::string tag, int x, int y)
{
    // Sets the member variables of the Level class
    this->lvlName = lvlName; // Set the level name
    this->x = x; // Set the X dimension
    this->y = x; // Set the Y dimension (Note: Should be 'this->y = y;' instead of 'this->y = x;')
    this->tag = tag; // Set the tag (e.g., "room")
}
```
{% endcode %}

A level is created via the `Level` class as it will make it easier to add entities to the level afterwards.

{% code title="Objects" %}
```cpp
#pragma once
#include <string>
#include "Components.h"
#include "Game.h"

class Object
{
public:
    Object()
    {
        CreateObject();
    }

    ~Object()
    {
        DeleteObject();
    }

    // Abstract methods to be overridden by derived classes
    virtual void CreateObject() = 0;  // Virtual method to create the object
    virtual void DeleteObject() = 0;  // Virtual method to delete the object

    // Add a transform component to the game object
    void AddTransform(int x, int y, int width, int height, float scale)
    {
        gameObject->addComponent<TransformComponent>(x, y, width, height, scale);
    }

    // Add a sprite component to the game object
    void AddSprite(const char* path)
    {
        gameObject->addComponent<SpriteComponent>(path);
    }

    // Add a collider component to the game object
    void AddCollider(std::string tag)
    {
        gameObject->addComponent<ColliderComponent>(tag);
    }

    // Get the transform component of the game object
    TransformComponent GetTransform()
    {
        return gameObject->getComponent<TransformComponent>();
    }

    Entity* gameObject;  // Pointer to the associated game object
};

class Player : public Object
{
public:
    Player()
    {
        CreateObject();
    }

    ~Player()
    {
        DeleteObject();
    }

    // Create a player object with specific attributes
    void CreatePlayer(int x, int y)
    {
        AddTransform(x, y, 24, 24, 2);
        AddSprite("Assets/Bucket Knight Concept.png");
        AddCollider("player");
        gameObject->addComponent<KeyboardController>();  // Add keyboard controller specific to player
    }
};

class Wall : public Object
{
public:
    Wall()
    {
        CreateObject();
    }

    ~Wall()
    {
        DeleteObject();
    }

    // Create a wall object with specific attributes
    void CreateWall(int x, int y, int width, int height, const char* texture)
    {
        AddTransform(x, y, width, height, 1);
        AddSprite(texture);
        AddCollider("wall");
    }
};

class Trigger : public Object
{
public:
    Trigger()
    {
        CreateObject();
    }

    ~Trigger()
    {
        DeleteObject();
    }

    // Create a trigger object with specific attributes
    void CreateTrigger(int x, int y, int width, int height, const char* texture, std::string tag)
    {
        AddTransform(x, y, width, height, 1);
        AddSprite(texture);
        AddCollider(tag);
    }
};
```
{% endcode %}

The `Objects.h` file stores the base `Object` class and allows me to create objects faster (as shown below).

For Example:

If I was creating a wall without the new objects system I would write:

```cpp
auto& wall(manager.addEntity());
wall.addComponent<TransformComponent>(500, 500, 300, 20);
wall.addComponent<SpriteComponent>("Assets/FloorTexture.png");
wall.addComponent<ColliderComponent>("wall");
wall.addGroup(groupMap);
```

But with the new objects system I can write:

```cpp
auto wall = new Wall();
wall->CreateWall(204, 120, 432, 24, "Assets/FloorTexture2.png");
wall->gameObject->addGroup(groupForeground);
```

This will make it so much easier to create entities and add them to the game which will speed up development time.

You can find the rest of the solution[ here](https://github.com/Marling-CS-Projects/ODY-ELLIOT-Project/tree/cycles/Bucket%20Knight%20-%20Cycle%203).

### Challenges

A big challenge of this was getting collisions to work properly but I eventually thought of a solution to this and made it so the `TransformComponent` stores the previous position of the entity and, when the player collides with a wall, the player's position is set back to its previous position.

An easier part of this cycle is making the viewport scale as I found SDL has a function called `SDL_RenderSetLogicalSize` which does this for me.

However, the biggest challenge of this cycle was memory. When switching between rooms the memory incremented by approximately 3MB as the previous room wasn't being disposed of properly. This caused the game to crash as all the rooms visited were trying to be rendered at the same time. This was solved by fixing the tile-map deletion algorithm so these rooms were no longer in memory and were being rendered underneath the current room.

## Testing

For reference, the trigger with the white circle is the `backTrigger` and the trigger with the red circle is the `frontTrigger`. These triggers allow the player to move between the dungeon's rooms.

<figure><img src="../.gitbook/assets/image (7).png" alt="" width="563"><figcaption><p>A screenshot from YouTube (<a href="https://youtu.be/dw7ssOx5V9M">https://youtu.be/dw7ssOx5V9M</a>)</p></figcaption></figure>

<table><thead><tr><th width="90">Test</th><th width="141">Instructions</th><th>What I expect</th><th width="163">What actually happens</th><th>Pass/Fail</th></tr></thead><tbody><tr><td>1</td><td>Player touches frontTigger</td><td>The next room appears</td><td>As expected</td><td>Pass</td></tr><tr><td>2</td><td>Player touches backTigger</td><td>The previous room appears</td><td>As expected</td><td>Pass</td></tr><tr><td>3</td><td>Player walks into the wall</td><td>The player doesn't pass through the wall</td><td>As expected</td><td>Pass</td></tr><tr><td>4</td><td>Player touches frontTigger while in the final room</td><td>The player stays in the final room</td><td>As expected</td><td>Pass</td></tr><tr><td>5</td><td>Player touches backTigger</td><td>The player stays in the first room</td><td>As expected</td><td>Pass</td></tr></tbody></table>

### Evidence

{% embed url="https://youtu.be/dw7ssOx5V9M" %}
The video above shows the third cycle of my game ([https://youtu.be/dw7ssOx5V9M](https://youtu.be/dw7ssOx5V9M))
{% endembed %}

The YouTube video (shown above) demonstrates the dungeon generation system working correctly as well as the wall collisions working properly. It also shows the viewport scaling to the correct size.

# 2.2.3 Cycle 3

## Design

This cycle is about creating the dungeon generator which will create the layout of the dungeon the player has to play through.

In this cycle I have also added some quality-of-life features for development such as a new `Object` class to make it easier to create entities.

As well as that, I added viewport scaling so the user can play the game at any window size.

### Objectives

In this cycle I aim to:

* [x] Create a Dungeon Layout Generator
* [x] Have each room connect to each other
* [x] New Level Creation System
* [x] Dungeon Walls with Collision
* [x] Streamlined Entity Creation System
* [x] Viewport Scaling

### Usability Features

Viewport Scaling - Allows the user to play the game at any window size.

### Key Variables

| Variable Name | Use                                               |
| ------------- | ------------------------------------------------- |
| numRooms      | How many rooms there are in the dungeon.          |
| currentRoom   | Stores the value of the room the player is in.    |
| currentLayout | Stores the current layout of the current dungeon. |

### Pseudocode

{% code title="Dungeon Creator" %}
```cpp
Dungeon(int numRooms) // acts as a class constructor
{
    this.numRooms = numRooms
    this.rooms = GetRooms()
    this.currentRoom = 0
}

vector<string> GetRooms()
{
    // returns all the names of the text files the rooms are stored in 
    return vector<string>
    {
        "Room1.txt",
        "Room2.txt",
        "Room3.txt"
    }
}

void GenerateLayout()
{	
    this->currentLayout = {}
    currentLayout.size() = numRooms
    
    currentLayout.start() = new Level("RoomSTART") // adds the start room

    for (int i = 0; i < numRooms - 2; i++)
    {
        currentLayout[i + 1] = new Level(rooms[(std::rand() % (this->rooms.size() - 2)) + 2])
    }

    currentLayout.end() = new Level("RoomEND") // adds the end room
}

void DrawCurrentRoom()
{
    if (currentRoom < 0) { currentRoom = 0 }
    else if (currentRoom > currentLayout.size() - 1) { currentRoom = currentLayout.size() - 1 }
    currentLayout.at(currentRoom)->BuildLevel()
}

int numRooms
vector<string> rooms{}
vector<Level*> currentLayout
int currentRoom
```
{% endcode %}

The dungeon generator will be created as an object and will render the current level the player is in.

## Development

### Outcome

{% code title="Dungeon.cpp" %}
```cpp
#include "Dungeon.h"
#include <iostream>

Dungeon::Dungeon()
{
	this->numRooms = 5;
	this->rooms = GetRooms();
	this->currentRoom = 0;
}

Dungeon::Dungeon(int numRooms)
{
	this->numRooms = numRooms;
	this->rooms = GetRooms();
	this->currentRoom = 0;
}

void Dungeon::GenerateLayout()
{
	this->currentLayout = {};
	currentLayout.resize(numRooms);

	currentLayout[0] = new Level("RoomSTART"); // adds the start room
	currentLayout[0]->tag = "start";

	std::srand(time(NULL));

	for (int i = 0; i < numRooms - 2; i++)
	{
		currentLayout[i + 1] = new Level(rooms[(std::rand() % (this->rooms.size() - 2)) + 2]);
		currentLayout[i + 1]->tag = "room";
	}

	currentLayout[numRooms-1] = new Level("RoomEND"); // adds the end room
	currentLayout[numRooms-1]->tag = "end";
}

void Dungeon::DrawCurrentRoom()
{
	if (currentRoom < 0) { currentRoom = 0; }
	else if (currentRoom > currentLayout.size() - 1) { currentRoom = currentLayout.size() - 1; }
	currentLayout.at(currentRoom)->BuildLevel();
}
```
{% endcode %}

{% code title="Level.cpp" %}
```cpp
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
	// There is currently no destructor
}

void Level::SetVariables(std::string lvlName, std::string tag, int x, int y)
{
	this->lvlName = lvlName;
	this->x = x;
	this->y = x;
	this->tag = tag;
}
```
{% endcode %}

A level is created via the `Level` class as it will make it easier to add entities to the level afterwards.

{% code title="Objects.h" %}
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

	virtual void CreateObject();
	virtual void DeleteObject();

	void AddTransform(int x, int y, int width, int height, float scale)
	{
		gameObject->addComponent<TransformComponent>(x, y, width, height, scale);
	}

	void AddSprite(const char* path)
	{
		gameObject->addComponent<SpriteComponent>(path);
	}

	void AddCollider(std::string tag)
	{
		gameObject->addComponent<ColliderComponent>(tag);
	}

	TransformComponent GetTransform()
	{
		return gameObject->getComponent<TransformComponent>();
	}

	Entity* gameObject;

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

	void CreatePlayer(int x, int y)
	{
		AddTransform(x, y, 24, 24, 2);
		AddSprite("Assets/Bucket Knight Concept.png");
		AddCollider("player");
		gameObject->addComponent<KeyboardController>();
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

If I was creating a wall without Objects.h I would write:

```cpp
auto& wall(manager.addEntity());
wall.addComponent<TransformComponent>(500, 500, 300, 20);
wall.addComponent<SpriteComponent>("Assets/FloorTexture.png");
wall.addComponent<ColliderComponent>("wall");
wall.addGroup(groupMap);
```

But now I can just write:

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

However, the biggest challenge of this cycle was memory. When switching between rooms the memory incremented by approximately 3MB as the previous room wasn't being disposed of properly. This caused the game to crash as all the rooms visited were all trying to be rendered at the same time. This was solved by fixing the tile-map deletion algorithm so these rooms where no longer in memory and being rendered underneath the current room.

## Testing

For reference, the trigger with the white circle is the `backTrigger` and the trigger with the red circle is the `frontTrigger`. These triggers allow the player to move between the dungeon's rooms.

<figure><img src="../.gitbook/assets/image (7).png" alt="" width="563"><figcaption><p>A screenshot from YouTube (<a href="https://youtu.be/dw7ssOx5V9M">https://youtu.be/dw7ssOx5V9M</a>)</p></figcaption></figure>

<table><thead><tr><th width="90">Test</th><th width="141">Instructions</th><th>What I expect</th><th width="163">What actually happens</th><th>Pass/Fail</th></tr></thead><tbody><tr><td>1</td><td>Player touches frontTigger</td><td>The next room appears</td><td>As expected</td><td>Pass</td></tr><tr><td>2</td><td>Player touches backTigger</td><td>The previous room appears</td><td>As expected</td><td>Pass</td></tr><tr><td></td><td></td><td></td><td></td><td></td></tr></tbody></table>

### Evidence

{% embed url="https://youtu.be/dw7ssOx5V9M" %}
The video above shows the third cycle of my game ([https://youtu.be/dw7ssOx5V9M](https://youtu.be/dw7ssOx5V9M))
{% endembed %}

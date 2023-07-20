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
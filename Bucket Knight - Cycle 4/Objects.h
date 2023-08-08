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

	void CreatePlayer(int x, int y, int health)
	{
		AddTransform(x, y, 24, 24, 2);
		AddSprite("Assets/Bucket Knight Concept.png");
		AddCollider("player");
		gameObject->addComponent<InputController>();
		gameObject->addComponent<PlayerComponent>(health, 100);
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

class Bullet : public Object
{
public:

	Bullet()
	{
		CreateObject();
	}

	~Bullet()
	{
		DeleteObject();
	}

	void CreateBullet(int x, int y, int width, int height, const char* texture, std::string tag, Vector2D dir, float speed, float damage, float distance)
	{
		AddTransform(x, y, width, height, 1);
		AddSprite(texture);
		AddCollider(tag);
		gameObject->addComponent<ProjectileComponent>(speed, damage, distance, dir);
	}
};

class PlayerHeart : public Object
{

public:
	PlayerHeart()
	{
		CreateObject();
	}

	~PlayerHeart()
	{
		DeleteObject();
	}

	void CreatePlayerHeart(int x, int y, PlayerComponent* player, int position)
	{
		AddTransform(x, y, 24, 24, 2);
		AddSprite("Assets/HeartON.png");
		gameObject->addComponent<HeartComponent>(player, position);
	}
};

class EMelee : public Object
{
public:
	EMelee()
	{
		CreateObject();
	}

	~EMelee()
	{
		DeleteObject();
	}

	void CreateMeleeEnemy(int x, int y, int width, int height, const char* texture, std::string tag, TransformComponent* destination)
	{
		AddTransform(x, y, width, height, 2);
		AddSprite(texture);
		AddCollider(tag);
		gameObject->addComponent<MeleeEnemy>(destination, 0.75f, 1);
	}
};

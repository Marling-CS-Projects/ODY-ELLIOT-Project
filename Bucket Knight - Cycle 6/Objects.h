#pragma once
#include <string>
#include "Components.h"

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
		entity->addComponent<TransformComponent>(x, y, width, height, scale);
	}

	void AddSprite(const char* path)
	{
		entity->addComponent<SpriteComponent>(path);
	}

	void AddCollider(std::string tag)
	{
		entity->addComponent<ColliderComponent>(tag);
	}

	TransformComponent GetTransform()
	{
		if (this->entity->hasComponent<TransformComponent>())
		{
			return this->entity->getComponent<TransformComponent>();
		}
		this->entity->addComponent<TransformComponent>(0, 0);

		return this->entity->getComponent<TransformComponent>();
	}

	Game* GetGame();
	TransformComponent* GetPlayerTransform();

	Entity* entity;

};

class Player : public Object
{
public:
	Player()
	{
		CreateObject();
	}

	Player(int x, int y, int health)
	{
		CreateObject();
		CreatePlayer(x, y, health);
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
		entity->addComponent<InputController>();
		entity->addComponent<PlayerComponent>(health, 100);
	}
};

class Wall : public Object
{
public:
	Wall()
	{
		CreateObject();
	}

	Wall(int x, int y, int width, int height, const char* texture)
	{
		CreateObject();
		CreateWall(x, y, width, height, texture);
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

	Trigger(int x, int y, int width, int height, int scale, const char* texture, std::string tag)
	{
		CreateObject();
		CreateTrigger(x, y, width, height, scale, texture, tag);
	}

	~Trigger()
	{
		DeleteObject();
	}

	void CreateTrigger(int x, int y, int width, int height, int scale, const char* texture, std::string tag)
	{
		AddTransform(x, y, width, height, scale);
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

	Bullet(int x, int y, int width, int height, const char* texture, std::string tag, Vector2D dir, float speed, float damage, float distance)
	{
		CreateObject();
		CreateBullet(x, y, width, height, texture, tag, dir, speed, damage, distance);
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
		entity->addComponent<ProjectileComponent>(speed, damage, distance, dir);
	}
};

class PlayerHeart : public Object
{

public:
	PlayerHeart()
	{
		CreateObject();
	}

	PlayerHeart(int x, int y, PlayerComponent* player, int position)
	{
		CreateObject();
		CreatePlayerHeart(x, y, player, position);
	}

	~PlayerHeart()
	{
		DeleteObject();
	}

	void CreatePlayerHeart(int x, int y, PlayerComponent* player, int position)
	{
		AddTransform(x, y, 24, 24, 2);
		AddSprite("Assets/HeartON.png");
		entity->addComponent<HeartComponent>(player, position);
	}
};

class EMelee : public Object
{
public:
	EMelee()
	{
		CreateObject();
	}

	EMelee(int x, int y, int width, int height, const char* texture, std::string tag, TransformComponent* destination)
	{
		CreateObject();
		CreateMeleeEnemy(x, y, width, height, texture, tag, destination);
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
		entity->addComponent<MeleeEnemy>(GetPlayerTransform(), 0.75f, 1, GetGame());
	}
};

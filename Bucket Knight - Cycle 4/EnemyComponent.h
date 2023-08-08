#pragma once
#include "Components.h"

class EnemyComponent : public Component
{
public:
	EnemyComponent()
	{
		this->dest = nullptr;
		this->transform = nullptr;
		this->health = 0;
	}
	~EnemyComponent()
	{
		this->entity->destroy();
	}

	bool isAlive()
	{
		if (health > 0)
		{
			return true;
		}

		return false;
	}

	virtual void hit()
	{
		health -= 1;
	}

	TransformComponent* dest;
	TransformComponent* transform;
	int health;
	float speed;
};

class MeleeEnemy : public EnemyComponent
{
public:
	MeleeEnemy(TransformComponent* destination, float speed, int health)
	{
		dest = destination;
		this->health = health;
		this->transform = nullptr;
		this->speed = speed;
	}

	~MeleeEnemy()
	{
		this->entity->destroy();
	}

	void init() override
	{
		if (!entity->hasComponent<TransformComponent>())
		{
			entity->addComponent<TransformComponent>();
		}

		transform = &entity->getComponent<TransformComponent>();

		transform->speed = this->speed;
	}
	
	void update() override
	{
		if (!isAlive())
		{
			this->entity->destroy();
		}

		Vector2D destpos = dest->position;
		Vector2D dir = dir.normalize(destpos - transform->position);
		
		transform->velocity = dir;
	}
};




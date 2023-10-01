#pragma once
#include "Components.h"
#include "Game.h"

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

	void hit()
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
	MeleeEnemy(TransformComponent* destination, float speed, int health, Game* game)
	{
		this->dest = destination;
		this->health = health;
		this->transform = nullptr;
		this->speed = speed;
		this->game = game;
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
			//game->RemoveEnemyGroup(this->entity);
			this->entity->destroy();
		}

		Vector2D destpos = dest->position;
		
		Vector2D dir = dir.normalize(destpos - transform->position);
		
		transform->velocity = dir;
	}

	Game* game;
};

class MagicEnemy : public EnemyComponent
{
public:

	MagicEnemy(TransformComponent* destination, int health, Game* game, int cooldown)
	{
		this->dest = destination;
		this->health = health;
		this->transform = nullptr;
		this->game = game;
		this->cooldown = cooldown;

		this->frameToWaitFor = game->GetFrames() + this->cooldown;
	}

	~MagicEnemy()
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

		transform->speed = 0;
	}

	void update() override
	{

		if (!isAlive())
		{
			this->entity->destroy();
		}

		Vector2D destpos{ dest->position.x - 12, dest->position.y -12 };

		Vector2D dir = dir.normalize(destpos - transform->position);

		if (frameToWaitFor <= game->GetFrames() && this->entity->hasComponent<SpriteComponent>() && isAlive())
		{
			game->CreateEnemyBullet(transform->position.x + 12, transform->position.y + 12, 12, 12, "Assets/EnemyMagic.png", "enemybullet", dir, 2, 1, 800, "Magic");
			frameToWaitFor = game->GetFrames() + cooldown;
		}
	}
	
	int cooldown;
	int frameToWaitFor;
	Game* game;
};

class GunEnemy : public EnemyComponent
{
public:

	GunEnemy(TransformComponent* destination, float speed, int health, Game* game, int cooldown)
	{
		this->dest = destination;
		this->health = health;
		this->transform = nullptr;
		this->game = game;
		this->cooldown = cooldown;
		this->speed = speed;

		this->frameToWaitFor = game->GetFrames() + this->cooldown;
	}

	~GunEnemy()
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

		Vector2D destpos{ dest->position.x - 12, dest->position.y - 12 };

		Vector2D dir = dir.normalize(destpos - transform->position);

		if (frameToWaitFor <= game->GetFrames() && this->entity->hasComponent<SpriteComponent>() && isAlive())
		{
			game->CreateEnemyBullet(transform->position.x + 12, transform->position.y + 12, 12, 12, "Assets/Hairball.png", "enemybullet", dir, 2, 1, 200, "hair");
			frameToWaitFor = game->GetFrames() + cooldown;
		}

		transform->velocity = dir;
	}

	int cooldown;
	int frameToWaitFor;
	Game* game;
};


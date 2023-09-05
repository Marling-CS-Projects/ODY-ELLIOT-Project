#pragma once
#include "Components.h"

class PlayerComponent : public Component
{

public:

	PlayerComponent(int health, int cooldownTime)
	{
		this->health = health;
		this->cooldown = cooldownTime;
		canBeHit = true;
	}

	~PlayerComponent()
	{
		entity->destroy();
	}
	
	void StopGame();

	void update() override
	{
		if (health < 1)
		{
			StopGame();
		}
		else if (frameToWaitFor <= frames)
		{
			canBeHit = true;
		}

		frames += 1;
	}

	void hit(Entity * enemy)
	{
		if (canBeHit)
		{
			health -= 1;
			canBeHit = false;
			frameToWaitFor = frames + cooldown;
		}
	}

	bool canBeHit;
	int frames;
	int cooldown;
	int frameToWaitFor;
	int health;
};